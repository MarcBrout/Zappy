using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EndGameGui : MonoBehaviour {

	public void EndgameShow (string winner)
	{
		Text Wteam;
		Text Wmessage;

		Wmessage = GameObject.Find ("EndGameText").GetComponent<Text> ();
		Wteam = GameObject.Find ("WinnerText").GetComponent<Text> ();
		Wteam.enabled = true;
		Wteam.text = winner;
		Wmessage.enabled = true;
		Wmessage.text = "CONGRATS ! THE WINNER TEAM IS ";
	}

	public void Start()
	{
		GameObject.Find ("EndGameImage").GetComponent<Image> ().enabled = false;
		GameObject.Find ("WinnerText").GetComponent<Text> ().enabled = false;
		GameObject.Find ("EndGameText").GetComponent<Text> ().enabled = false;
	}
}
