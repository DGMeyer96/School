using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bomb : MonoBehaviour
{
    public float bombDamage = 100.0f;
    public float lifetime = 3.0f;

    private void Start()
    {
        Destroy(gameObject, lifetime);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        
        if (collision.gameObject.tag == "Enemy")
        {
            Health enemyHealth = collision.gameObject.GetComponent<Health>();
            enemyHealth.DamageHealth(bombDamage);
            Destroy(gameObject);
        }
        

        Debug.Log(collision.gameObject.name);

        //Destroy(collision.gameObject);
    }
}
