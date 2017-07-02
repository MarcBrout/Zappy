using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class InterpretServerResponse : MonoBehaviour
{
    public UpdateManager updateManager;
    private Dictionary<string, Action<string[]>> commands;

    private void Awake()
    {
        commands = new Dictionary<string, Action<string[]>>();

        commands["bct"] = updateManager.UpdateCell;
        commands["msz"] = updateManager.MapSizeUpdate;
        commands["pnw"] = updateManager.NewPlayer;
        commands["plv"] = updateManager.UpdatePlayerLvl;
        commands["pin"] = updateManager.UpdatePlayerInv;

        commands["ppo"] = updateManager.UpdatePlayerPos;
        commands["pex"] = updateManager.PlayerExpulse;
        commands["pic"] = updateManager.StartIncantation;
        commands["pie"] = updateManager.EndIncantation;
        commands["enw"] = updateManager.LayEgg;
        commands["eht"] = updateManager.HatchingEgg;
        commands["edi"] = updateManager.EggDied;
        commands["pdr"] = updateManager.Put;
        commands["pgt"] = updateManager.Take;
        commands["sgt"] = updateManager.UpdateUnitTime;
        commands["seg"] = updateManager.EndGame;
        commands["tna"] = updateManager.TeamName;
        commands["pdi"] = updateManager.PlayerDied;
        commands["ebo"] = updateManager.ConnectPlayerForEgg;
        commands["pbc"] = updateManager.Broadcast;

    }

    public void InterpretResponse(string response)
    {
        string[] line = response.Split('\n');

        foreach (string l in line)
        {
            string[] arg = l.Split(' ');

            if (commands != null && commands.ContainsKey(arg[0]))
                commands[arg[0]](arg);
        }
    }

}
