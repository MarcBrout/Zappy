using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnManager : MonoBehaviour
{
    public TeamInfoManager teamInfoManager;
    public GameObject playerPrefab;
    public GameObject eggPrefab;
    public GameObject incantPrefab;
    public Transform eggRoot;
    public Transform incantRoot;

    public List<Player> players;
    public List<Egg> eggs;
    public List<Incantation> incantationList;

    public Map map;
    public Material[] body;
    public Material[] arms;

    private Dictionary<string, int> teamMaterial;
    private int teamIndex = 0;

    public void SpawnPlayer(int id, int x, int y, int orientation, int level, string team)
    {
        if (map.cells != null)
        {
            Vector3 pos = map.cells[x, y].transform.position;
            GameObject go = Instantiate(playerPrefab);
            Player player = go.GetComponent<Player>();

            go.name = "Player_" + id;
            player.gridPos = new Vector2(x, y);
            player.offset = map.GetRandomMeshPos();
            player.transform.position = map.cells[x, y].transform.position;// + player.offset;
            player.team = team;
            player.id = id;
            player.level = level;
            players.Add(player);
            player.orientation = (Player.Orientation)orientation;
            player.nexGgridPos = player.gridPos;
            player.nextOrientation = player.orientation;
            player.transform.eulerAngles = ConvertOrientation((Player.Orientation)orientation);
            player.LevelUp(level);
            if (teamMaterial != null && teamMaterial.ContainsKey(team) && teamMaterial[team] < body.Length)
            {
                SkinnedMeshRenderer skmr = player.transform.GetChild(1).GetChild(1).GetComponent<SkinnedMeshRenderer>();
                Material[] mats = skmr.materials;
                mats[0] = body[teamMaterial[team]];
                mats[4] = arms[teamMaterial[team]];
                skmr.materials = mats;
            }
        }
    }

    private void Update()
    {
        teamInfoManager.Reset();
        for (int i = 0; i < players.Count; i++)
        {
            teamInfoManager.UpdateTeamInfo(players[i]);
        }
    }

    public void AddTeam(string teamName)
    {
        if (teamMaterial == null)
            teamMaterial = new Dictionary<string, int>();
        if (!teamMaterial.ContainsKey(teamName))
        {
            teamMaterial[teamName] = teamIndex;
            ++teamIndex;
        }
    }

    public void SpawnEgg(Vector2 pos, int id, string team)
    {
        GameObject go = Instantiate(eggPrefab, map.GetRandomCasePos((int)pos.x, (int)pos.y) + new Vector3(0, 0.5f, 0), eggPrefab.transform.rotation, eggRoot);
        Egg newEgg = go.GetComponent<Egg>();
        newEgg.id = id;
        newEgg.team = team;
        eggs.Add(newEgg);
        newEgg.Pop();
    }

    public Player FindPlayerById(int id)
    {
        return players.Find((x) => x.id == id);
    }

    public Egg FindEggById(int id)
    {
        return eggs.Find((x) => x.id == id);
    }

    public Vector3 ConvertOrientation(Player.Orientation orientation)
    {
        switch (orientation)
        {
            case Player.Orientation.NORTH:
                return new Vector3(0, 0, 0);
            case Player.Orientation.EAST:
                return new Vector3(0, 90, 0);
            case Player.Orientation.SOUTH:
                return new Vector3(0, 180, 0);
            case Player.Orientation.WEST:
                return new Vector3(0, 270, 0);
        };
        return Vector3.zero;
    }

    public void SpawnIncant(Vector2 pos)
    {
        GameObject go =
            Instantiate(incantPrefab, map.cells[(int)pos.x, (int)pos.y].transform.position, incantPrefab.transform.rotation, incantRoot);
        Incantation newIncant = go.GetComponent<Incantation>();
        newIncant.setGridPos(pos);
        incantationList.Add(newIncant);
        newIncant.PlayIncantation();
    }
}
