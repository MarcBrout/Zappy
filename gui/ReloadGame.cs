using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ReloadGame : MonoBehaviour 
{
	public Button button;

	public void Start()
	{
		Button _button = button.GetComponent<Button>();
		_button.onClick.AddListener(Reload);
	}

	public void Reload()
	{
		SceneManager.LoadScene(SceneManager.GetActiveScene().name, LoadSceneMode.Single);
	}
}
