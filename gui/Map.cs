using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class Map : MonoBehaviour
{

    public static readonly Vector3 North = new Vector3(0, 0, 1);
    public static readonly Vector3 East = new Vector3(1, 0, 0);
    public static readonly Vector3 South = new Vector3(0, 0, -1);
    public static readonly Vector3 West = new Vector3(-1, 0, 0);
    public static readonly Vector3 Up = new Vector3(0, 1, 0);
    public static readonly Vector3 Down = new Vector3(0, -1, 0);

    public Transform root;
    public GameObject prefab;
    public Vector2 dimension;
    public ZappyCell[,] cells;

    Mesh mesh;

    public Vector3 ScaleFactor
    {
        get { return mesh.bounds.size; }
    }

    public void CreateMap()
    {
        cells = new ZappyCell[(int)dimension.x, (int)dimension.y];
        mesh = prefab.GetComponent<MeshFilter>().sharedMesh;
        for (int x = 0; x < dimension.x; x++)
        {
            for (int y = 0; y < dimension.y; y++)
            {
                int newY = (int)dimension.y - y - 1;
                GameObject go = Instantiate(prefab, new Vector3(mesh.bounds.size.x * x, 0, mesh.bounds.size.z * y), Quaternion.identity, transform);
                go.name = "cube(" + x + "," + newY + ")";
                cells[x, newY] = go.GetComponent<ZappyCell>();
                cells[x, newY].gridPos = new Vector2(x, newY);
            }
        }
    }

    public Vector3 WorldToGrid(Vector3 worldPoint)
    {
        Vector3 vec = new Vector3(worldPoint.x / mesh.bounds.size.x, 0, worldPoint.z / mesh.bounds.size.z);
        vec.x = MyCeil(vec.x);
        vec.z = MyCeil(vec.z);
        return vec;
    }

    public Vector3 GridToWorld(Vector3 gridPoint)
    {
        return (new Vector3(gridPoint.x * mesh.bounds.size.x, 0, gridPoint.z * mesh.bounds.size.z));
    }

    public bool Contains(Vector3 vec)
    {
        return (vec.x >= 0 && vec.z >= 0 && vec.x < cells.GetLength(0) && vec.z < cells.GetLength(1));
    }

    public void UpdateCell(int x, int y, int food, int libenate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    {
        if (cells != null && x >= 0 && y >= 0 && x < cells.GetLength(0) && y < cells.GetLength(1))
            cells[x, y].UpdateCell(food, libenate, deraumere, sibur, mendiane, phiras, thystame);
    }

    int MyCeil(double i)
    {
        int r;

        if (i < 0)
        {
            i *= -1;
            r = (int)Math.Ceiling(i);
            r *= -1;
        }
        else
            r = (int)Math.Ceiling(i);
        return r;
    }

    public Vector3 GetRandomMeshPos()
    {
        float newX = UnityEngine.Random.Range(mesh.bounds.min.x + mesh.bounds.extents.x / 4, mesh.bounds.max.x - mesh.bounds.extents.x / 4);
        float newY = UnityEngine.Random.Range(mesh.bounds.min.z + mesh.bounds.extents.z / 4, mesh.bounds.max.z - mesh.bounds.extents.z / 4);

        return new Vector3(newX, 0, newY);
    }

    public Vector3 GetRandomCasePos(int x, int y)
    {
        return GetRandomMeshPos() + cells[x, y].transform.position;
    }
}
