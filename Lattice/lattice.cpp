#include "lattice.h"

void HexagonLattice::Initialize(sf::RenderWindow* window) {
    this->window = window;

    //create hex
    float radius = this->hexSize / 2.0f;
    float spaceBetweenCrack = (radius / 2.0f) * (std::tan(Math::toRad(15))) * 2;
    float height = sqrt(radius * radius - (radius/2) * (radius/2));

    for (int col = 0; col < numCols; ++col) {
        std::vector<Hexagon> hex;
        this->hexagons.push_back(hex);

        for (int row = 0; row < numRows; ++row) {
            float x = col * (radius * 1.5f);
            float y = this->hexSize * (row) - (row * spaceBetweenCrack) + ((col % 2) * height);
            this->hexagons[col].push_back(createHexagon(hexSize, this->startingPos + sf::Vector2f(x, y), col, row));
        }
    }

    //add hex neighbor
    //top
    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row < numRows; row++) {
            //top top
            Hexagon* toptop = this->getHexAtIndex(col, row-1); 
            this->hexagons[col][row].neighborHex.push_back(toptop);

            //top right
            Hexagon* topright = this->getHexAtIndex(col+1, (col % 2 == 0) ? row-1 : row);
            this->hexagons[col][row].neighborHex.push_back(topright);

            //bottom right
            Hexagon* bottomright = this->getHexAtIndex(col+1, (col % 2 == 0) ? row : row+1);
            this->hexagons[col][row].neighborHex.push_back(bottomright);

            //bottom bottom
            Hexagon* bottombottom = this->getHexAtIndex(col, row+1); 
            this->hexagons[col][row].neighborHex.push_back(bottombottom);

            //bottom left
            Hexagon* bottomleft = this->getHexAtIndex(col-1, (col % 2 == 0) ? row : row+1);
            this->hexagons[col][row].neighborHex.push_back(bottomleft);

            //top left
            Hexagon* topleft = this->getHexAtIndex(col-1, (col % 2 == 0) ? row-1 : row);
            this->hexagons[col][row].neighborHex.push_back(topleft);
        }
    }
    
}

void HexagonLattice::Update(sf::Event event) {

}

void HexagonLattice::Visualize(sf::Event event) {
    sf::Vector2f mousePos = Math::convertToFloatVec(sf::Mouse::getPosition(*this->window));
    for (const auto& col : hexagons) {
        for (const auto& hexagon: col) {
            this->window->draw(hexagon.vertexArr);
        }
    }

    //test
    /*for (int col = 0; col < numCols; ++col) {
        for (int row = 0; row < numRows; ++row) {
            auto hex = this->getHexAtIndex(col, row);
            hex->ChangeToOriginalColor();
        }
    }

    auto hex = this->getHexAtPos(mousePos.x, mousePos.y);
    if (hex != nullptr) {
        hex->ChangeColor(sf::Color::Red);

        for (const auto nei: hex->neighborHex) {
            if (nei != nullptr) {
                nei->ChangeColor(sf::Color::Red);
            }
        }
    }*/
}

void HexagonLattice::LateUpdate() {

}

void HexagonLattice::Reset() {
    this->hexagons.clear();
}

Hexagon HexagonLattice::createHexagon(float size, sf::Vector2f screenPos, int col, int row) {
    Hexagon hex;
    hex.Initialize(this->window, size, screenPos, col, row);

    return hex;
}

/*Hexagon* HexagonLattice::getHexAtIndex(int col, int row) {
    if (this->hexagons.empty() || col < 0 || col >= (int) this->hexagons.size() || row < 0 || row >= (int) this->hexagons[0].size()) {
        //std::cout << "Hex not found!";
        return nullptr;
    }

    return &this->hexagons[col][row];
}*/

//wrapped around method
Hexagon* HexagonLattice::getHexAtIndex(int col, int row) {
    if (this->hexagons.empty()) {
        // Handle empty hexagon grid
        return nullptr;
    }

    // Adjust column index for wrapping around
    col = (col + this->hexagons.size()) % this->hexagons.size();

    // Adjust row index for wrapping around
    row = (row + this->hexagons[col].size()) % this->hexagons[col].size();

    return &this->hexagons[col][row];
}


//inaccurate
Hexagon* HexagonLattice::getHexAtPos(float x, float y) {
    sf::Vector2f point(x, y);
    int colIdx = 0;
    for (const auto& col : hexagons) {
        int rowIdx = 0;
        for (const auto& hexagon: col) {
            sf::Vector2f center = hexagon.screenPos;
            float radius = hexagon.size / 2.0f;

            if (Math::Distance(point, center) <= radius) {
                return this->getHexAtIndex(colIdx, rowIdx);
            }
            rowIdx++;
        }
        colIdx++;
    }
    return nullptr;
}

Hexagon* HexagonLattice::getMidHex() {
    return this->getHexAtIndex(this->numCols/2, this->numRows/2);
}