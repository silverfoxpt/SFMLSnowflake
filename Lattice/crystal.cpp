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

    for (int i = 0; i < this->cols; i++) {
        for (int j = 0; j < this->rows; j++) {
            a[i][j] = 0;
            b[i][j] = c[i][j] = 0.0;
            d[i][j] = p1;
        }
    }

    //initialize lattice center
    sf::Vector2i center(std::max(0, cols/2-1), std::max(0, rows/2-1));
    a[center.x][center.y] = 1;
    c[center.x][center.y] = 1.0;
    b[center.x][center.y] = d[center.x][center.y] = 0;

    //initialize sets
    //inside
    this->inside.push_back(this->lattice->getHexAtIndex(center.x, center.y));

    //boundary
    for (auto nei: this->inside[0]->neighborHex) {
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

    //test
}

void Crystal::Update(sf::Event event) {
}

void Crystal::Visualize(sf::Event event) {

}

void Crystal::LateUpdate() {

}

void Crystal::Reset() {
    this->a.clear();
    this->b.clear();
    this->c.clear();
    this->d.clear();

    this->inside.clear();
    this->boundary.clear();
    this->outside.clear();
    this->outsideBoundary.clear();
}