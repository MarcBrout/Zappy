using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class Egg : MonoBehaviour
{
    private Vector2 position;
    public int     id;

    // Audio
    public float       volume;
    public AudioClip   eggPopSound;
    public AudioClip   eggCrackSound;
    public AudioSource audio;
    public GameObject egg;
    public string team;
    
    public void Pop()
    {
        audio.Stop();
        audio.PlayOneShot(eggPopSound, volume);
    }

    public void Crack()
    {
        audio.Stop();
        audio.PlayOneShot(eggCrackSound, volume);
    }

    public Vector2 getPosition()
    {
        return position;
    }

    public void setPosition(Vector2 _pos)
    {
        position = _pos;
    }

    public int getId()
    {
        return id;
    }

    public void setId(int _id)
    {
        id = _id;
    }
}