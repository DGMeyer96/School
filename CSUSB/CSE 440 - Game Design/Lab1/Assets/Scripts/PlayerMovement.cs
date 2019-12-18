using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerMovement : MonoBehaviour
{
    [Header("Keyboard Input: ")]
    public KeyCode moveLeft = KeyCode.A;
    public KeyCode moveRight = KeyCode.D;
    public KeyCode jump = KeyCode.Space;

    [Header("Horizontal Speed Settings: ")]
    public float speedMultiplier = 5.0f;    // Play around with this setting to optimize the right speed for the player in the inspector.

    [Header("Jumping Settings: ")]
    public float jumpPower = 5.0f;          // Play around with this setting to optimize the right height for jumping in the inspector.
    public Transform groundDetection;       // Initialize with the transform that is the empty gameobject that is positioned at the bottom of where your player is positioned.
    public LayerMask ground;                // Check for layer named ground in the inspector.
    public Transform winDetection;
    public LayerMask win;

    public Text winText;

    private Rigidbody2D rb;                 // Used to apply forces with a 2D gameobject
    private bool isGrounded;                // Used to check the space below the player as ground or not
    private bool winner;
    private int jumping = 0;

    /// <summary>
    /// Start is called before the first frame update
    /// </summary>
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();   // Initialize the Rigidbody2D object with this gameobject's Rigidbody2D component that is attached to it in the inspector.
        winText.gameObject.SetActive(false);
    }

    /// <summary>
    /// Fixed Update is called once per fixed frame.
    /// Use physical behaviors (or anything involving the rigidbody) in this function.
    /// </summary>
    private void FixedUpdate()
    {
        isGrounded = Physics2D.OverlapCircle(groundDetection.position, 0.1f, ground);   // Check to see if objects that are layered as Ground are detected within the overlap circle around the empty gameobject ground detection. 

        //Debug.Log("isGrounded: " + isGrounded);

        if (isGrounded)                                                                 // Check if player is grounded.
        {
            jumping = 0;
            if (Input.GetKeyDown(jump) && jumping != 2)                                                 // Check if jump key is pressed.
            {
                rb.AddForce(Vector2.up * jumpPower, ForceMode2D.Impulse);               // Add an impulsive force to the rigidbody of the gameobject.
                Debug.Log("I am jumping. " + jumping);
                jumping++;
            }
        }
        else if (Input.GetKeyDown(jump) && jumping != 2)                                                 // Check if jump key is pressed.
        {
            rb.AddForce(Vector2.up * (jumpPower * 1.2f), ForceMode2D.Impulse);               // Add an impulsive force to the rigidbody of the gameobject.
            Debug.Log("I am jumping. " + jumping);
            jumping++;
        }

        winner = Physics2D.OverlapCircle(winDetection.position, 0.1f, win);

        //Debug.Log("You Win? - " + winner);

        //winText.gameObject.SetActive(winner);

        if(winner)
        {
            winText.gameObject.SetActive(true);
        }
    }

    /// <summary>
    /// Update is called once per frame
    /// </summary>
    void Update()
    {
        Vector2 newMovement;                                                                                // Create a local variable to store the next movement calculation.

        if (Input.GetKey(moveLeft))                                                                         // Check if moveLeft key is pressed.
        {
            newMovement = new Vector2(rb.position.x - (Time.deltaTime * speedMultiplier), rb.position.y);   // Move the player along the x-axis using a speed multiplier in the left direction.
            rb.position = newMovement;                                                                      // Set the rigidbody position to the newMovement position that was just calculated.
        }
        if (Input.GetKey(moveRight))                                                                        // Check if moveRight key is pressed.
        {
            newMovement = new Vector2(rb.position.x + (Time.deltaTime * speedMultiplier), rb.position.y);   // Move the player along the x-axis using a speed multiplier in the right direction.
            rb.position = newMovement;                                                                      // Set the rigidbody position to the newMovement position that was just calculated.
        }
    }
}
