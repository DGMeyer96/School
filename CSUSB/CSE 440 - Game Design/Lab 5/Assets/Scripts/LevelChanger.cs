using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelChanger : MonoBehaviour
{
    public Animator animator;

    private int sceneToLoad;

    // Update is called once per frame
    void Update()
    {
        
    }

    public void FadeLevelChange(int sceneIndex)
    {
        sceneToLoad = sceneIndex;
        animator.SetTrigger("FadeOut");
    }

    public void FadeOutComplete()
    {
        SceneManager.LoadScene(sceneToLoad);
    }
}
