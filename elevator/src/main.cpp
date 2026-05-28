#include <iostream>
#include <set>

enum Direction
{
    UP,
    DOWN,
    IDLE
};

enum DoorState
{
    OPEN,
    CLOSE
};

class Elevator
{
private:
    int currentFloor = 0;
    Direction direction;
    DoorState doorState;

    std::set<int> upQueue;
    std::set<int> downQueue;
    std::set<int> queue;

public:
    void move()
    {
        // for (auto const floor : queue)
        // {
        //     std::cout << floor << std::endl;
        // }

        while (queue.size() != 0)
        {

            for (auto it = queue.begin(); it != queue.end();)
            {
                std::cout << "Going to Floor " << *it << std::endl;
                currentFloor = *it;
                openDoor();
                it = queue.erase(it);
                closeDoor();
            }
            std::cout << "All ops done, Elevator position: " << currentFloor << " floor" << std::endl;
        }
    };
    void addRequest(int floor)
    {
        queue.insert(floor);

        if (upQueue.empty() && downQueue.empty())
        {
            upQueue.insert(floor);
        }
    };
    void openDoor()
    {
        std::cout << "--opening door--" << std::endl;
        doorState = DoorState::OPEN;
    };
    void closeDoor()
    {
        std::cout << "--closing door--" << std::endl;
        doorState = DoorState::CLOSE;
    };
};

int main()
{
    Elevator e1;

    e1.addRequest(1);

    e1.addRequest(5);
    e1.addRequest(2);

    e1.move();

    return 0;
}