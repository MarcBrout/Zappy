using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class SliderOnPointerUp : MonoBehaviour, IPointerUpHandler
{

    public NetworkAsync net;
    Slider slider;
    float oldValue;

    void Start()
    {
        slider = GetComponent<Slider>();
        oldValue = slider.value;
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        if (slider.value != oldValue)
        {
            oldValue = slider.value;
            UpdateFrequency();
        }
    }

    public void UpdateSlider(int value)
    {
        if (slider.value != value)
        { 
            slider.value = value;
            oldValue = slider.value;
        }
    }

    public void UpdateFrequency()
    {
        net.Send("sst " + (int)slider.value + "\n");
    }
}