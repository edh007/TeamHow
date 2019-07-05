#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 ParticleColor;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

flat in int fragmentType;

uniform float Time;			// Delta time

// Shader effect variables
uniform bool RippleToggle;	// ripple toggle
uniform	vec2 WavePhase;		// x,y waves phase
uniform bool WaveToggle;	// wave toggle

uniform float BlurAmount;	// blur amount
uniform bool BlurToggle;	// blur toggle

uniform float SobelAmount;	// sobel amount
uniform bool SobelToggle;	// sobel toggle

uniform bool InverseToggle;	// inverse toggle

vec4 RippleEffect( vec2 texCoord )
{
	vec2 cPos = -1.0 + 2.0 * texCoord.xy / vec2(1, 1).xy;
	float cLength = length(cPos);

	vec2 uv = texCoord.xy/vec2(1, 1).xy+(cPos/cLength)*cos(cLength*63.0-Time*4.0)*0.03;
	vec3 col = texture2D(myTextureSampler,uv).xyz;

	return vec4(col,1.0);
}

void main()
{
	vec4 temp;	
	vec2 new_tex = UV;
	
	// Wave effect...
	if(WaveToggle) {
		float x = cos( 25.0*new_tex.y + 30.0*new_tex.x + 6.28*WavePhase.x) * 0.05;
		float y = sin( 25.0*new_tex.y + 30.0*new_tex.x + 6.28*WavePhase.y) * 0.05;
		new_tex = vec2(new_tex.x+x, new_tex.y+y);
	}
	
    if(fragmentType == 2)
	{
		//color = (texture(myTextureSampler, new_tex) * ParticleColor);
	    temp = (texture(myTextureSampler, new_tex) * ParticleColor);
	    if(temp.a < 0.1)
            discard;
	    color = temp;
	}

	else if(fragmentType == 3)
	{
	  temp = (texture(myTextureSampler, new_tex) * ParticleColor);
	  color = temp;
	}
	else
	{
	  temp = (texture(myTextureSampler, new_tex) * ParticleColor);
	  if(temp.a < 0.1)
        discard;
	  color = temp;
	}
	
	// Ripple Effect...	
	if (RippleToggle) {
		vec4 ripColor = RippleEffect(new_tex);
		color = vec4(ripColor.x*color.x, ripColor.y*color.y, ripColor.z*color.z, color.w);
	}
		
	// Blur effect...
	if (BlurToggle)
	{
		const float blurH = 1.0 / 300.0;
		const float blurV = 1.0 / 300.0;
		vec4 sum = vec4(0.0);
		for (int x = -4; x <= 4; x++)
			for (int y = -4; y <= 4; y++)
				sum += texture(
					myTextureSampler, vec2(new_tex.x + x * blurH, new_tex.y + y * blurV)) / BlurAmount;
		color = vec4(sum.xyz, temp.w);
	}
	
	// Sobel effect...
	if (SobelToggle)
	{
		vec4 top         = texture(myTextureSampler, vec2(new_tex.x, new_tex.y + 1.0 / SobelAmount));
		vec4 bottom      = texture(myTextureSampler, vec2(new_tex.x, new_tex.y - 1.0 / SobelAmount));
		vec4 left        = texture(myTextureSampler, vec2(new_tex.x - 1.0 / SobelAmount, new_tex.y));
		vec4 right       = texture(myTextureSampler, vec2(new_tex.x + 1.0 / SobelAmount, new_tex.y));
		vec4 topLeft     = texture(myTextureSampler, vec2(new_tex.x - 1.0 / SobelAmount, new_tex.y + 1.0 / SobelAmount));
		vec4 topRight    = texture(myTextureSampler, vec2(new_tex.x + 1.0 / SobelAmount, new_tex.y + 1.0 / SobelAmount));
		vec4 bottomLeft  = texture(myTextureSampler, vec2(new_tex.x - 1.0 / SobelAmount, new_tex.y - 1.0 / SobelAmount));
		vec4 bottomRight = texture(myTextureSampler, vec2(new_tex.x + 1.0 / SobelAmount, new_tex.y - 1.0 / SobelAmount));
		vec4 sx = -topLeft - 2 * left - bottomLeft + topRight   + 2 * right  + bottomRight;
		vec4 sy = -topLeft - 2 * top  - topRight   + bottomLeft + 2 * bottom + bottomRight;
		color = sqrt(sx * sx + sy * sy);
	}
	
	// Inverse effect...
	if (InverseToggle)
	{
		vec3 manip = vec3(1.0, 1.0, 1.0) - color.xyz;
		color = vec4(manip, color.w);
	}

	if(fragmentType == 0)
	{
	  temp = vec4(1.0, 1.0, 1.0, texture(myTextureSampler, new_tex).r);
	  temp = ParticleColor * temp;
	  if(temp.a < 0.1)
        discard;
	  color = temp;
	}
}
