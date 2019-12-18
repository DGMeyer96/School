//Ball.vert
uniform vec3 iVel;
uniform vec3 iPos;
uniform float time1;

varying float prevY;

void main(void)
{
	float s = 1000.0;
	float g = -10.0;
	float t;
	vec3 minimum = vec3(0.0, -2.0, 0.0);
	float cor = 0.752; //coefficient of resitution for a hand ball
	t = time1 / s;

	float t1;	//time at jump
	float t2;	//time at peak
	float t3;	//time when at bottom
	float dt;	//change in time
	//float prevY;
	float dy = 0.0;	//change in y

	vec4 objPos;
	objPos = gl_Vertex;

	objPos.xyz = objPos.xyz + iPos.xyz;
	t1 = time1 / s; //initial time

	objPos.x = objPos.x + iVel.x * t;   
	objPos.y = objPos.y + iVel.y * t + g / (2.0) * t * t;   
	objPos.z = objPos.z + iVel.z * t;
	
	dy = objPos.y - iPos.y;

	if(objPos.y < dy) //ball is now falling, record peak time
	{
		t2 = t;
		dt = t2 - t1;
	}

	t3 = t;	//record time as ball falls

	if((t3 - dt) == dt)	//if change in falling time = change in rising time, ball is at initial position / floor, bounce
	{
		objPos.y = reflect(-objPos.y, normalize(iPos.y)) * cor;
	}

	//dy = objPos.y - prevY;
	//prevY = objPos.y;

	/*
	if(objPos.y < iPos.y)
	{
		//objPos.y = reflect(-objPos.y, normalize(iPos.y)) * cor;
	}
	*/

		//objPos.y = reflect(-objPos.y, normalize(iPos.y)) * cor;
		//objPos.x = reflect(objPos.x, normalize(iPos.x));

    gl_Position = gl_ModelViewProjectionMatrix * objPos;

	prevY = objPos.y;
}