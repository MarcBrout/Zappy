using UnityEngine;
using System.Collections;

[RequireComponent (typeof(AudioSource))]
public class Incantation : MonoBehaviour
{
    // gridPos
    private Vector2 gridPos = new Vector2(0, 0);

    // Audio
    public float volume;
    public  AudioClip   incantationMainSound;
    public  AudioClip   incantationEndSound;
    public  AudioClip   incantationLevelUpSound;
    public  AudioSource audio;

    // Particle
    public ParticleSystem particle;

    // Id of incant
    private static int nextid = 0;
    private int        id;

    private void Awake()
    {
        particle.Stop();
        id = nextid;
        nextid++;
        audio = GetComponent<AudioSource>();
/*        incantationMainSound    = (AudioClip)Resources.Load("incantation.ogg");
        incantationEndSound     = (AudioClip)Resources.Load("incantation_end.ogg");
        incantationLevelUpSound = (AudioClip)Resources.Load("levelup.ogg");
*/
    }

    public void PlayIncantation()
    {
        audio.Stop();
        audio.loop = true;
        audio.clip = incantationMainSound;
        audio.volume = volume;
        audio.Play();
        particle.Stop();
        particle.Play();
    }

    public void StopIncantation(bool success)
    {
        audio.loop = false;
        audio.Stop();
        if (success)
        {
            particle.Stop();
            audio.PlayOneShot(incantationLevelUpSound, volume);
        }
        else
        {
            particle.Stop();
            audio.PlayOneShot(incantationEndSound, volume);
        }
    }

    public void setGridPos(Vector2 pos)
    {
        gridPos = pos;
    }

    public Vector2 getGridPos()
    {
        return gridPos;
    }

    public int getId()
    {
        return id;
    }
}