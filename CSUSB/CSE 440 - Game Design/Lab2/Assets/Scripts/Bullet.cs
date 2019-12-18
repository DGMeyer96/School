using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    public float speedMultiplier = 5.0f;
    public bool useHorizontalPhysicsMovement = true;

    private bool isMovingRight = true;
    private Rigidbody2D rb;

    private void Awake()
    {
        GameObject player = GameObject.FindGameObjectWithTag("Player");

        if(player.transform.localScale.x > 0)
        {
            isMovingRight = true;
        }
        else if(player.transform.localScale.x < 0)
        {
            isMovingRight = false;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        
        if(useHorizontalPhysicsMovement)
        {
            rb = GetComponent<Rigidbody2D>();

            if (isMovingRight)
            {
                rb.AddForce(Vector2.right * Time.deltaTime * speedMultiplier, ForceMode2D.Impulse);
            }
            else
            {
                rb.AddForce(Vector2.left * Time.deltaTime * speedMultiplier, ForceMode2D.Impulse);
            }
        }
        
    }

    // Update is called once per frame
    void Update()
    {
        //transform.position = new Vector2(transform.position.x + (Time.deltaTime * speedMultiplier) ,transform.position.y);

        if (!useHorizontalPhysicsMovement)
        {
            if (isMovingRight)
            {
                transform.Translate(Vector2.right * Time.deltaTime * speedMultiplier);
            }
            else
            {
                transform.Translate(Vector2.left * Time.deltaTime * speedMultiplier);
            }
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "Enemy")
        {
            //Destroy(collision.gameObject);
            collision.gameObject.GetComponent<EnemyController>().health--;
        }

        Destroy(gameObject);
    }
}
