using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PauseHandler : MonoBehaviour
{
    public static bool gamePaused = false;

    public GameObject pauseMenuUI;
    public Player player;

    public Animator animator;

    // Update is called once per frame
    void Update()
    {
        if(Input.GetButtonDown("Cancel"))
        {
            Debug.Log("Pausing game");

            if(gamePaused)
            {
                Resume();
            }
            else
            {
                Pause();
            }
        }
    }

    public void Resume()
    {
        pauseMenuUI.SetActive(false);
        Time.timeScale = 1f;
        EnableControl();
        gamePaused = false;
    }

    private void Pause()
    {
        pauseMenuUI.SetActive(true);
        Time.timeScale = 0f;
        DisableControl();
        gamePaused = true;
    }

    public void MainMenu()
    {
        Debug.Log("Loading: Main Menu");
        SceneManager.LoadScene(0);
    }

    public void RestartGame()
    {
        Debug.Log("Restarting Game");
        SceneManager.LoadScene(1);
    }

    public bool GetGamePaused()
    {
        return gamePaused;
    }

    private void DisableControl()
    {
        player.GetComponent<Player>().enabled = false;
    }

    private void EnableControl()
    {
        player.GetComponent<Player>().enabled = true;
    }
}
