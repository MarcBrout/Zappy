using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class MainMusicManager : MonoBehaviour 
{
	public AudioSource audioSource;
	public AudioClip   endTheme;
	
	public void PlayEndTheme()
	{
		audioSource.Stop();
		audioSource.loop = true;
		audioSource.clip = endTheme;
		audioSource.volume = 1;
		audioSource.Play();
	}
}
