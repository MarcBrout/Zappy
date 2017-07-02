using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ZappyCell : MonoBehaviour
{
    public Vector2 gridPos;
    public ZappyObjects inventory;
    public GameObject[] gems;
    public List<Vector3> spawnPoints;
    
    public void Awake()
    {
        spawnPoints = new List<Vector3>();
        inventory = new ZappyObjects();
        foreach (Transform t in transform.GetChild(0))
        {
            spawnPoints.Add(t.position);
        }

        for (int i = 0; i < gems.Length; i++)
        {
            gems[i].transform.position = GetSpawnPoint();
        }
    }

    private Vector3 GetSpawnPoint()
    {
        int r = Random.Range(0, spawnPoints.Count);

        Vector3 vec = spawnPoints[r];
        spawnPoints.Remove(spawnPoints[r]);
        return (vec);
    }

    public void UpdateCell(int food, int libenate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    {
        if (inventory == null)
            inventory = new ZappyObjects();

        inventory.UpdateValues(food, libenate, deraumere, sibur, mendiane, phiras, thystame);

        if (food <= 0) gems[0].SetActive(false); else gems[0].SetActive(true);
        if (libenate <= 0) gems[1].SetActive(false); else gems[1].SetActive(true);
        if (deraumere <= 0) gems[2].SetActive(false); else gems[2].SetActive(true);
        if (sibur <= 0) gems[3].SetActive(false); else gems[3].SetActive(true);
        if (mendiane <= 0) gems[4].SetActive(false); else gems[4].SetActive(true);
        if (phiras <= 0) gems[5].SetActive(false); else gems[5].SetActive(true);
        if (thystame <= 0) gems[6].SetActive(false); else gems[6].SetActive(true);
    }

}
