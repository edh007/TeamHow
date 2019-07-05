#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec4 ParticleColor;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 Animation;
uniform int Flip;
uniform int Type;
uniform vec2 Screensize;

//Use for Particle.
uniform mat4 projection;
uniform vec2 offset;
uniform vec4 color;
uniform float scale;

//Use for Fog of War
uniform int FowType;

flat out int fragmentType;

void main(){

    //if type is text
    if(Type == 0)
	{
		gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
		UV = vertexUV;
		ParticleColor = color;

	}

	//if type is sprite.
    else if(Type == 1)
	{
		// Output position of the vertex, in clip space : MVP * position
		gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
		vec4 newTexCoord = Animation * vec4(vertexUV, 0, 1); //
		
		if(Flip == 1)  //NORMAL
		    UV = vec2(newTexCoord.x, newTexCoord.y);
		else if(Flip == -1)  //FLIP
	        UV = vec2(-newTexCoord.x, newTexCoord.y);

		ParticleColor = color;
	}

	//if type is particle.
	else if(Type == 2)
	{
        UV = vertexUV;
		gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
        //gl_Position = MVP * vec4((vertexPosition_modelspace.xy * scale) + offset, 0.0, 1.0);
		ParticleColor = color;
	}
    //if type is fow:light
	else if(Type == 3)
	{
	    //gl_Position =  MVP * vec4(((vertexPosition_modelspace.xy*scale) + offset), vertexPosition_modelspace.z,1);
		gl_Position =  MVP * vec4( (  (vertexPosition_modelspace.x*scale) + offset.x  ), (  (vertexPosition_modelspace.y*scale) + offset.y  ), 
		vertexPosition_modelspace.z,1 );
		UV = vertexUV;
		//ParticleColor = color;
	    if(FowType == 0) //BLACK
		{
		    ParticleColor = vec4(1,1,1,1);
		}
		else if(FowType == 1) //GRAY
		{
		    ParticleColor = vec4(0.4,0.4,0.4,0.3);
		}
		else if(FowType == 2) //WHITE
		{
		    ParticleColor = vec4(0.5,0.5,0.5,0);
		}
	}

    fragmentType = Type;
	

	
	//if particle, pass uv coordinates.
	//if(Type == 2)
	//{
      //vec4 newTexCoord = Animation * vec4(vertexUV, 0, 1);
	  //UV = vec2(newTexCoord.x, newTexCoord.y);
	//}
}