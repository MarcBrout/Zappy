using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ClickManager : MonoBehaviour
{
    public NetworkAsync net;
    public InventoryUI  invUI;

    private GameObject Click()
    {
        RaycastHit hit;
        Ray screenToWorldPos = Camera.main.ScreenPointToRay(Input.mousePosition);

        if (Physics.Raycast(screenToWorldPos, out hit, Mathf.Infinity, 1 << LayerMask.NameToLayer("Clickable")))
        {
            return hit.transform.gameObject;
        }
        return null;
    }

    private void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Player player = null;
            GameObject go = Click();
            ZappyObjects inv = null;

            if (go != null)
            {

                if (go.tag == "Player")
                {
                    player = go.GetComponent<Player>();
                    if (player != null)
                    {
                        net.Send("pin " + player.id.ToString() + "\n");
                        inv = player.inventory;
                    }
                }
                else
                {
                    ZappyCell cell = go.GetComponent<ZappyCell>();
                    net.Send("bct " + cell.gridPos.x + " " + cell.gridPos.y + "\n");
                    inv = cell.inventory;
                }
                if (inv != null)
                {
                    invUI.go = go;
                    invUI.activeInventory = inv;
                }
            }
        }
    }
}
