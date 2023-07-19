#include "crystal.h"

void Crystal::Initialize(sf::RenderWindow* window, HexagonLattice* lattice) {
    this->window = window;
    this->lattice = lattice;

    this->cols = lattice->numCols;
    this->rows = lattice->numRows;

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
    auto firstHex = this->lattice->getHexAtIndex(center.x, center.y);
    this->inside.push_back(firstHex);

    //boundary
    for (auto nei: firstHex->neighborHex) {
        this->boundary.push_back(nei);
    }

    //outside
    for (int i = 0; i < this->cols; i++) {
        for (int j = 0; j < this->rows; j++) {
            if (i != center.x || j != center.y) {
                auto hex = this->lattice->getHexAtIndex(i, j);
                this->outside.push_back(hex);

                //outside boundary
                auto found = std::find(boundary.begin(), boundary.end(), hex);
                if (found == boundary.end()) { this->outsideBoundary.push_back(hex);  }
            }
        }
    }
    std::cout << "Crystal initialized!" << '\n';
}

void Crystal::Update(sf::Event event) {
    this->Diffusion();
    this->Freezing();
    this->Attachment();
    this->Melting();
    this->Perturb();
}

void Crystal::Visualize(sf::Event event) {
    for (auto hex: this->inside) {
        hex->ChangeColor(sf::Color::Cyan);
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

    this->inside.clear();
    this->boundary.clear();
    this->outside.clear();
    this->outsideBoundary.clear();
    this->all.clear();
}

void Crystal::Diffusion() {
    std::vector<std::vector<float>> d2(this->cols, std::vector<float>(this->rows, 0.0));
    for (auto hex: this->outsideBoundary) {
        float total = this->d[hex->col][hex->row];

        for (auto nei: hex->neighborHex) {
            total += this->d[nei->col][nei->row];
        }

        d2[hex->col][hex->row] = total / 7.0;
    }

    for (auto hex: this->boundary) {
        float total = this->d[hex->col][hex->row];

        for (auto nei: hex->neighborHex) {
            //if nei is inside
            if (a[nei->col][nei->row] == 1) {
                total += this->d[hex->col][hex->row];
            }
            else {
                total += this->d[nei->col][nei->row];
            }
        }
        d2[hex->col][hex->row] = total / 7.0;
    }
    
    for (int i = 0; i < this->cols; i++) {
        for (int j = 0; j < this->rows; j++) {
            this->d[i][j] = d2[i][j];
        }
    }
}

void Crystal::Freezing() {
    for (auto hex: this->boundary) {
        this->b[hex->col][hex->row] += (1 - this->k2)   * this->d[hex->col][hex->row];
        this->c[hex->col][hex->row] += this->k2         * this->d[hex->col][hex->row];
        this->d[hex->col][hex->row] = 0.0;
    }
}

void Crystal::Attachment() {
    std::vector<std::pair<int, int>> toAdd;

    for (auto hex: this->boundary) {
        //calculated number of attached crystal
        int nt = 0;
        float boundaryMass = this->d[hex->col][hex->row];
        for (auto nei: hex->neighborHex) {
            nt              += this->a[nei->col][nei->row];
            boundaryMass    += this->d[nei->col][nei->row];
        }

        if (nt == 0) {std::cout << "Error: Boundary miscalculated" << '\n'; continue;}

        //if 1 to 2
        if (nt == 1 || nt == 2) {
            if (this->b[hex->col][hex->row] >= this->b3) {
                //add crystal
                toAdd.push_back(std::make_pair(hex->col, hex->row));
            }
        }
        
        //if 3
        if (nt == 3) {
            if (this->b[hex->col][hex->row] >= 1 
                || (boundaryMass < this->o3 && this->b[hex->col][hex->row] >= this->a3)) 
            {
                //add crystal
                toAdd.push_back(std::make_pair(hex->col, hex->row));
            }
        }

        //if 4 to 6
        if (nt >= 4) {
            //add crystal
            toAdd.push_back(std::make_pair(hex->col, hex->row));
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
        float prevb = this->b[hex->col][hex->row], prevc = this->c[hex->col][hex->row];
        this->b[hex->col][hex->row]     = (1 - this->u4) * this->b[hex->col][hex->row];
        this->c[hex->col][hex->row]     = (1 - this->y4) * this->c[hex->col][hex->row];
        this->d[hex->col][hex->row]     += (this->u4) * prevb + (this->y4) * prevc;
    }
}

void Crystal::Perturb() {
    for (auto hex: this->all) {
        float sign = Randomize::rand.RandomFloat01() > 0.5 ? 1 : -1;
        this->d[hex->col][hex->row] += this->d[hex->col][hex->row] * (1 + sign * this->o5);
    }
}

void Crystal::AddToCrystal(int col, int row) {
    auto hex = this->lattice->getHexAtIndex(col, row);

    //add to inside
    this->inside.push_back(hex);

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
    
    for (auto nei: hex->neighborHex) {
        int neiCol = nei->col, neiRow = nei->row;

        if (this->a[neiCol][neiRow] == 0) { //if not already inside
            //add to boundary
            this->boundary.push_back(nei);

            //remove from outside boundary
            found = std::find(this->outsideBoundary.begin(), this->outsideBoundary.end(), nei);
            if (found != this->outsideBoundary.end()) {
                this->outsideBoundary.erase(found);
            }
        }
    }
}

void Crystal::ModCrystalValue(int col, int row) {
    auto hex = this->lattice->getHexAtIndex(col, row);

    //mod values
    this->a[hex->col][hex->row] = 1;
    this->c[hex->col][hex->row] += this->b[hex->col][hex->row];
    this->b[hex->col][hex->row] = 0;
}