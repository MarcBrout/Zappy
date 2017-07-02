using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class ZappyObjects {

    public int Food { get; set; }
    public int Linemate { get; set; }
    public int Deraumere { get; set; }
    public int Sibur { get; set; }
    public int Mendiane { get; set; }
    public int Phiras { get; set; }
    public int Thystame { get; set; }

    public ZappyObjects()
    {
        Food = Linemate = Deraumere = Sibur = Mendiane = Phiras = Thystame = 0;
    }

    public void UpdateValues(int food, int libenate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    {
        Food = food;
        Linemate = libenate;
        Deraumere = deraumere;
        Sibur = sibur;
        Mendiane = mendiane;
        Phiras = phiras;
        Thystame = thystame;
    }

    public void UpdateRessource(int ressource, int amount)
    {
        switch (ressource)
        {
            case 0:
                Food += amount;
                break;
            case 1:
                Linemate += amount;
                break;
            case 2:
                Deraumere += amount;
                break;
            case 3:
                Sibur += amount;
                break;
            case 4:
                Mendiane += amount;
                break;
            case 5:
                Phiras += amount;
                break;
            case 6:
                Thystame += amount;
                break;
        }
    }
}
