#include "crystal.h"

void Crystal::Initialize(sf::RenderWindow* window, HexagonLattice* lattice) {
    this->window = window;
    this->lattice = lattice;

    this->cols = lattice->numCols;
    this->rows = lattice->numRows;

    //set up neighborIdx
    this->neighborIdx.resize(this->cols, std::vector<std::vector<std::pair<int, int>>>(this->rows));
    for (int i = 0; i < this->cols; i++) {
        for (int j = 0; j < this->rows; j++) {
            auto hex = this->lattice->getHexAtIndex(i, j);

            for (auto nei: hex->neighborHex) {
                this->neighborIdx[i][j].push_back(std::make_pair(nei->col, nei->row));
            }
        }
    }

    //initialize lattice;
    this->a.resize(this->cols, std::vector<int>(this->rows));
    this->b.resize(this->cols, std::vector<float>(this->rows));
    this->c.resize(this->cols, std::vector<float>(this->rows));
    this->d.resize(this->cols, std::vector<float>(this->rows));
    //this->d2.resize(this->cols, std::vector<float>(this->rows));

    for (int i = 0; i < this->cols; i++) {
        for (int j = 0; j < this->rows; j++) {
            a[i][j] = 0;
            b[i][j] = c[i][j] = 0.0;
            //d[i][j] = this->d2[i][j] = p1;
            d[i][j] = p1;
        }
    }

    //initialize lattice center
    sf::Vector2i center(cols/2, rows/2);
    a[center.x][center.y] = 1;
    c[center.x][center.y] = 1.0;
    b[center.x][center.y] = d[center.x][center.y] = 0;

    //initialize sets
    //inside
    this->inside.insert(std::make_pair(center.x, center.y));

    //boundary
    for (auto nei: this->neighborIdx[center.x][center.y]) {
        this->boundary.insert(nei);
    }

    //outside
    for (int i = 0; i < this->cols; i++) {
        for (int j = 0; j < this->rows; j++) {
            if (i != center.x || j != center.y) {
                this->outside.insert(std::make_pair(i, j));

                //outside boundary
                auto found = std::find(boundary.begin(), boundary.end(), std::make_pair(i, j));
                if (found == boundary.end()) { this->outsideBoundary.insert(std::make_pair(i, j)); }
            }

            //all
            this->all.insert(std::make_pair(i, j));
        }
    }

    std::cout << "Crystal initialized!" << '\n';
}

void Crystal::Update(sf::Event event) {
    this->Diffusion();
    this->Freezing();
    this->Attachment();
    this->Melting();
    //this->Perturb();
}

void Crystal::Visualize(sf::Event event) {
    float maxValue = 5;
    for (auto idx: this->all) {
        auto hex = this->lattice->getHexAtIndex(idx.first, idx.second);

        //calculate value
        float value = 
            std::min((double) maxValue, this->c[idx.first][idx.second] + this->d[idx.first][idx.second] * 1.5) / maxValue;

        hex->ChangeColor(this->GetColorFromLightness(1 - value));
    }
}

void Crystal::LateUpdate() {

}

void Crystal::Reset() {
    this->a.clear();
    this->b.clear();
    this->c.clear();
    this->d.clear();
    //this->d2.clear();
    this->neighborIdx.clear();

    this->inside.clear();
    this->boundary.clear();
    this->outside.clear();
    this->outsideBoundary.clear();
    this->all.clear();
}

void Crystal::Diffusion() {
    std::vector<std::vector<float>> d2(this->cols, std::vector<float>(this->rows, 0.0));
    for (auto hex: this->outsideBoundary) {
        float total = this->d[hex.first][hex.second];

        for (auto nei: this->neighborIdx[hex.first][hex.second]) {
            total += this->d[nei.first][nei.second];
        }

        d2[hex.first][hex.second] = total / 7.0;
    }

    for (auto hex: this->boundary) {
        float total = this->d[hex.first][hex.second];

        for (auto nei: this->neighborIdx[hex.first][hex.second]) {
            //if nei is inside
            if (a[nei.first][nei.second] == 1) {
                total += this->d[hex.first][hex.second];
            }
            else {
                total += this->d[nei.first][nei.second];
            }
        }
        d2[hex.first][hex.second] = total / 7.0;
    }
    
    for (int i = 0; i < this->cols; i++) {
        for (int j = 0; j < this->rows; j++) {
            this->d[i][j] = d2[i][j];
        }
    }
}

void Crystal::Freezing() {
    for (auto hex: this->boundary) {
        this->b[hex.first][hex.second] += (1 - this->k2)   * this->d[hex.first][hex.second];
        this->c[hex.first][hex.second] += this->k2         * this->d[hex.first][hex.second];
        this->d[hex.first][hex.second] = 0.0;
    }
}

void Crystal::Attachment() {
    std::vector<std::pair<int, int>> toAdd;

    for (auto hex: this->boundary) {
        //calculated number of attached crystal
        int nt = 0;
        float boundaryMass = this->d[hex.first][hex.second];
        for (auto nei: this->neighborIdx[hex.first][hex.second]) {
            nt              += this->a[nei.first][nei.second];
            boundaryMass    += this->d[nei.first][nei.second];
        }

        if (nt == 0) {std::cout << "Error: Boundary miscalculated" << '\n'; continue;}

        //if 1 to 2
        if (nt == 1 || nt == 2) {
            if (this->b[hex.first][hex.second] >= this->b3) {
                //add crystal
                toAdd.push_back(hex);
            }
        }
        
        //if 3
        else if (nt == 3) {
            if (this->b[hex.first][hex.second] >= 1 
                || (boundaryMass < this->o3 && this->b[hex.first][hex.second] >= this->a3)) 
            {
                //add crystal
                toAdd.push_back(hex);
            }
        }

        //if 4 to 6
        else if (nt >= 4) {
            //add crystal
            toAdd.push_back(hex);
        }
    }

    for (auto hex: toAdd) {
        this->AddToCrystal(hex.first, hex.second);
    }

    for (auto hex: toAdd) {
        this->ModCrystalValue(hex.first, hex.second);
    }
}

void Crystal::Melting() {
    for (auto hex: this->boundary) {
        float prevb = this->b[hex.first][hex.second], prevc = this->c[hex.first][hex.second];
        this->b[hex.first][hex.second]     = (1 - this->u4) * this->b[hex.first][hex.second];
        this->c[hex.first][hex.second]     = (1 - this->y4) * this->c[hex.first][hex.second];
        this->d[hex.first][hex.second]     += (this->u4) * prevb + (this->y4) * prevc;
    }
}

void Crystal::Perturb() {
    for (auto hex: this->all) {
        float sign = Randomize::rand.RandomFloat01() > 0.5 ? 1 : -1;
        this->d[hex.first][hex.second] = this->d[hex.first][hex.second] * (1 + sign * this->o5);
    }
}

void Crystal::AddToCrystal(int col, int row) {
    auto hex = std::make_pair(col, row);

    //add to inside
    this->inside.insert(hex);

    //remove from outside
    auto found = std::find(this->outside.begin(), this->outside.end(), hex);
    if (found != this->outside.end()) {
        this->outside.erase(found);
    }

    //remove from boundary
    found = std::find(this->boundary.begin(), this->boundary.end(), hex);
    if (found != this->boundary.end()) {
        this->boundary.erase(found);
    }
    
    for (auto nei: this->neighborIdx[hex.first][hex.second]) {
        int neiCol = nei.first, neiRow = nei.second;

        if (this->a[neiCol][neiRow] == 0) { //if not already inside
            //add to boundary
            this->boundary.insert(nei);

            //remove from outside boundary
            found = std::find(this->outsideBoundary.begin(), this->outsideBoundary.end(), nei);
            if (found != this->outsideBoundary.end()) {
                this->outsideBoundary.erase(found);
            }
        }
    }
}

void Crystal::ModCrystalValue(int col, int row) {
    //mod values
    this->a[col][row] = 1;
    this->c[col][row] += this->b[col][row];
    this->b[col][row] = 0;
}

sf::Color Crystal::GetColorFromLightness(float lightness) {
    lightness = std::max(0.0f, std::min(1.0f, lightness)); // Clamp lightness between 0 and 1

    // Convert HSL to RGB
    float hue = 240.0f; // Blue hue
    float saturation = 100.0f; // Full saturation

    float c = (1 - std::abs(2 * lightness - 1)) * saturation / 100.0f;
    float x = c * (1 - std::abs(fmod(hue / 60.0f, 2) - 1));
    float m = lightness - c / 2;

    float r, g, b;
    if (hue >= 0 && hue < 60) {
        r = c;
        g = x;
        b = 0;
    } else if (hue >= 60 && hue < 120) {
        r = x;
        g = c;
        b = 0;
    } else if (hue >= 120 && hue < 180) {
        r = 0;
        g = c;
        b = x;
    } else if (hue >= 180 && hue < 240) {
        r = 0;
        g = x;
        b = c;
    } else if (hue >= 240 && hue < 300) {
        r = x;
        g = 0;
        b = c;
    } else { // hue >= 300 && hue < 360
        r = c;
        g = 0;
        b = x;
    }

    sf::Uint8 red = static_cast<sf::Uint8>((r + m) * 255);
    sf::Uint8 green = static_cast<sf::Uint8>((g + m) * 255);
    sf::Uint8 blue = static_cast<sf::Uint8>((b + m) * 255);

    return sf::Color(red, green, blue);
}