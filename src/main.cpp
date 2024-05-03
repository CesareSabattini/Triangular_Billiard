#include"classes/System.hpp"

int main(){
    System<double> system(1,2,2,40, 7, 5);
    system.simulate();
    std::cout<< system.getCollisions().size() << std::endl;
    std::cout << "Simulation complete." << std::endl;
    return 0;
}
