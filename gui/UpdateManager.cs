using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class UpdateManager : MonoBehaviour
{
    public SpawnManager spawnManager;
    public Map map;

    public static float frequency = 100;
    public GameObject endUI;
    public GameObject inventoryUI;
    public MainMusicManager mainMusicManager;
    public SliderOnPointerUp freqSlider;
    public static bool endGame = false;

    public void UpdateCell(string[] res)
    {
        if (res.Length == 10 && res[0] == "bct")
            map.UpdateCell(int.Parse(res[1]), int.Parse(res[2]), int.Parse(res[3]),
                int.Parse(res[4]), int.Parse(res[5]), int.Parse(res[6]), int.Parse(res[7]), int.Parse(res[8]),
                int.Parse(res[9]));
    }

    public void MapSizeUpdate(string[] res)
    {
        if (res.Length == 3 && res[0] == "msz")
        {
            map.dimension.x = int.Parse(res[1]);
            map.dimension.y = int.Parse(res[2]);
            if (map.cells == null)
                map.CreateMap();
        }
    }

    public void NewPlayer(string[] res)
    {
        if (res.Length == 7 && res[0] == "pnw")
        {
            spawnManager.SpawnPlayer(int.Parse(res[1]), int.Parse(res[2]), int.Parse(res[3]), int.Parse(res[4]), int.Parse(res[5]), res[6]);
        }
    }

    public void UpdatePlayerLvl(string[] res)
    {
        if (res.Length == 3 && res[0] == "plv")
        {
            Player p = spawnManager.FindPlayerById(int.Parse(res[1]));
            if (p != null)
            {
                p.LevelUp(int.Parse(res[2]));
                p.level = int.Parse(res[2]);
            }
        }
    }

    public void UpdatePlayerPos(string[] res)
    {
        if (res.Length == 5 && res[0] == "ppo")
        {
            Player p = spawnManager.FindPlayerById(int.Parse(res[1]));
            Player.Orientation orientation = (Player.Orientation)int.Parse(res[4]);
            int x = int.Parse(res[2]);
            int y = int.Parse(res[3]);
            if (p != null)
            {
                if (p.IsPositionDifferent(x, y))
                    StartCoroutine(p.Move(x, y));
                else if (p.IsOrientationDifferent(orientation))
                    StartCoroutine(p.Turn(orientation));
                p.nexGgridPos.x = x;
                p.nexGgridPos.y = y;
                p.nextOrientation = orientation;
            }
        }
    }

    public void UpdatePlayerInv(string[] res)
    {
        if (res.Length == 11)
        {
            Player p = spawnManager.FindPlayerById(int.Parse(res[1]));

            if (p != null)
            {
                p.inventory.Food = int.Parse(res[4]);
                p.inventory.Linemate = int.Parse(res[5]);
                p.inventory.Deraumere = int.Parse(res[6]);
                p.inventory.Sibur = int.Parse(res[7]);
                p.inventory.Mendiane = int.Parse(res[8]);
                p.inventory.Phiras = int.Parse(res[9]);
                p.inventory.Thystame = int.Parse(res[10]);
            }
        }
    }

    public void PlayerExpulse(string[] res)
    {
        if (res.Length == 2 && res[0] == "pex")
        {
            Player p = spawnManager.FindPlayerById(int.Parse(res[1]));
            if (p != null)
                StartCoroutine(p.Expulse());
        }
    }

    public void StartIncantation(string[] res)
    {
        int x;
        int y;
        Vector2 pos;

        if (res.Length >= 2)
        {
            x = int.Parse(res[1]);
            y = int.Parse(res[2]);
            pos = new Vector2(x, y);
            spawnManager.SpawnIncant(pos);
        }
    }

    public void EndIncantation(string[] res)
    {
        int x;
        int y;
        int success;
        Vector2 pos;

        if (res.Length != 4)
            return;
        x = int.Parse(res[1]);
        y = int.Parse(res[2]);
        success = int.Parse(res[3]);
        pos = new Vector2(x, y);
        Incantation incantation = spawnManager.incantationList.Find(incant => incant.getGridPos() == pos);
        if (incantation != null)
        {
            incantation.StopIncantation(success == 1);
            spawnManager.incantationList.Remove(incantation);
            StartCoroutine(DelayDestroy(incantation.gameObject, 2f));
        }
    }

    public void LayEgg(string[] res)
    {
        if (res.Length == 5)
        {
            int x = int.Parse(res[3]);
            int y = int.Parse(res[4]);
            int id = int.Parse(res[1]);
            Vector2 pos = new Vector2(x, y);

            Player p = spawnManager.FindPlayerById(int.Parse(res[2]));
            if (p != null)
                spawnManager.SpawnEgg(pos, id, p.team);
        }
    }

    public void HatchingEgg(string[] res)
    {
        if (res.Length == 2)
        {
            Egg egg = spawnManager.FindEggById(int.Parse(res[1]));

        }
    }

    public void ConnectPlayerForEgg(string[] res)
    {
        if (res.Length == 2)
        {
            Egg egg = spawnManager.FindEggById(int.Parse(res[1]));

            if (egg != null)
            {
                spawnManager.eggs.Remove(egg);
                egg.Crack();
                Destroy(egg.gameObject);
            }
        }
    }

    public void EggDied(string[] res)
    {
        if (res.Length == 2)
        {
            Egg egg = spawnManager.FindEggById(int.Parse(res[1]));

            spawnManager.eggs.Remove(egg);
            Destroy(egg.gameObject);
        }
    }

    public void Put(string[] res)
    {
        if (res.Length == 3)
        {
            Player p = spawnManager.FindPlayerById(int.Parse(res[1]));
            if (p != null)
            {
                p.inventory.UpdateRessource(int.Parse(res[2]), -1);
                p.Put();
            }
        }
    }

    public void Take(string[] res)
    {
        if (res.Length == 3)
        {
            Player p = spawnManager.FindPlayerById(int.Parse(res[1]));
            if (p != null)
            {
                p.inventory.UpdateRessource(int.Parse(res[2]), 1);
                p.Take();
            }
        }
    }

    public void PlayerDied(string[] res)
    {
        if (res.Length == 2)
        {
            int playerId = int.Parse(res[1]);
            Player player = spawnManager.FindPlayerById(playerId);
            if (player != null)
            {
                player.Die();
                spawnManager.players.Remove(player);
                StartCoroutine(DelayDestroy(player.gameObject, 1));
            }
        }
    }

    public void UpdateUnitTime(string[] res)
    {
        if (res.Length == 2 && res[0] == "sgt")
        {
            frequency = int.Parse(res[1]);
            freqSlider.UpdateSlider((int)frequency);
            foreach (Player p in spawnManager.players)
            {
                p.speed = 7 / frequency;
                p.UpdateAnimSpeed();

            }
        }
    }

    public void EndGame(string[] res)
    {
        if (res.Length == 2 && res[0] == "seg")
        {
            print("GameOver");
            endGame = true;
            inventoryUI.SetActive(false);
            endUI.SetActive(true);
            endUI.transform.GetChild(2).GetComponent<Text>().text = res[1].ToUpper();
            mainMusicManager.PlayEndTheme();
        }
    }

    public void Broadcast(string[] res)
    {
        if (res.Length < 3)
            return;
        int playerid = int.Parse(res[1]);
        Player player = spawnManager.FindPlayerById(playerid);
        if (player)
            StartCoroutine(ShowForSecond(player.exclamation, 2));
    }

    public void Disconnect()
    {
        GetComponent<NetworkAsync>().Disconnect();
    }

    private IEnumerator ShowForSecond(GameObject go, float seconds)
    {
        if (!go.activeSelf && go != null)
        {
            go.SetActive(true);
            yield return new WaitForSeconds(seconds);
            if (go != null)
                go.SetActive(false);
        }
    }

    public void TeamName(string[] res)
    {
        if (res.Length == 2)
        {
            spawnManager.AddTeam(res[1]);
        }
    }

    public static IEnumerator DelayDestroy(GameObject go, float delay)
    {
        yield return new WaitForSeconds(delay);
        Destroy(go);
    }

    public void ResetLevel()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
}