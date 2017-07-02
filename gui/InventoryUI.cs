using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InventoryUI : MonoBehaviour
{
    public Text title;
    public GameObject prefabsUI;
    public static Dictionary<string, Text> inventoryPair;
    public readonly string[] names = { "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame", "Food" };
    public Sprite[] img;
    public GameObject go;
    public ZappyObjects activeInventory;

   void Awake()
    {
        inventoryPair = new Dictionary<string, Text>();
        for (int i = 0; i < names.Length; i++)
        {
            GameObject go = Instantiate(prefabsUI, transform);
            go.name = names[i];
            go.transform.GetChild(0).GetComponent<Image>().sprite = img[i];
            go.transform.GetChild(0).GetComponent<Image>().preserveAspect = true;
            go.transform.GetChild(1).GetComponent<Text>().text = names[i];
            inventoryPair[names[i]] = go.transform.GetChild(2).GetComponent<Text>();
        }
    }

    private void Update()
    {
        if (go != null && activeInventory != null)
        {
            Player player = go.GetComponent<Player>();
            if (player)
                title.text = "Team: " + player.team + " Id: " + player.id + " Level: " + player.level;
            else
                title.text = go.name;

            UpdateUI("Food", activeInventory.Food);
            UpdateUI("Deraumere", activeInventory.Deraumere);
            UpdateUI("Linemate", activeInventory.Linemate);
            UpdateUI("Mendiane", activeInventory.Mendiane);
            UpdateUI("Phiras", activeInventory.Phiras);
            UpdateUI("Sibur", activeInventory.Sibur);
            UpdateUI("Thystame", activeInventory.Thystame);
        }
    }

    public void UpdateUI(string names, string value)
    {
        if (inventoryPair != null && inventoryPair.ContainsKey(names))
            inventoryPair[names].text = value;
    }

    public void UpdateUI(string names, int value)
    {
        if (inventoryPair != null && inventoryPair.ContainsKey(names))
            inventoryPair[names].text = value.ToString();
    }
}
