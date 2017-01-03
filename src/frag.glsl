#version 410 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec3 color1;
out vec3 color2;
out vec3 color3;
out vec3 color4;
out vec3 color5;

// Values that stay constant for the whole mesh.
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;
uniform sampler2D sampler4;
uniform sampler2D sampler5;


uniform mat4 MV;
uniform vec3 LightPosition_worldspace;

void main(){

	// Light properties
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 70.0f;
	
	// Material properties
//----------------------------------------------------
    
	vec3 mDiffuse1 = texture( sampler1, UV ).rgb;
	vec3 mAmbient1 = vec3(0.1,0.1,0.1) * mDiffuse1;
	vec3 mSpecular1 = vec3(0.3,0.3,0.3);
    

    vec3 mDiffuse2 = texture( sampler2, UV ).rgb;
    vec3 mAmbient2 = vec3(0.1,0.1,0.1) * mDiffuse2;
    vec3 mSpecular2 = vec3(0.3,0.3,0.3);
    

    vec3 mDiffuse3 = texture( sampler3, UV ).rgb;
    vec3 mAmbient3 = vec3(0.1,0.1,0.1) * mDiffuse3;
    vec3 mSpecular3 = vec3(0.3,0.3,0.3);
    
    
    vec3 mDiffuse4 = texture( sampler4, UV ).rgb;
    vec3 mAmbient4 = vec3(0.1,0.1,0.1) * mDiffuse4;
    vec3 mSpecular4 = vec3(0.3,0.3,0.3);
    

    vec3 mDiffuse5 = texture( sampler5, UV ).rgb;
    vec3 mAmbient5 = vec3(0.1,0.1,0.1) * mDiffuse5;
    vec3 mSpecular5 = vec3(0.3,0.3,0.3);
    
//----------------------------------------------------
    
	// Distance to the light
	float distance = length( LightPosition_worldspace - Position_worldspace );

	// Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	color1 =
		// Indirect lighting
		mAmbient1 +
		// The object's color
		mDiffuse1 * LightColor * LightPower * cosTheta / (distance*distance) +
		// Reflective
		mSpecular1 * LightColor * LightPower * pow(cosAlpha,4) / (distance*distance);
    
    color2 =
        mAmbient2 +
        mDiffuse2 * LightColor * LightPower * cosTheta / (distance*distance) +
        mSpecular2 * LightColor * LightPower * pow(cosAlpha,4) / (distance*distance);
    
    color3 =
        mAmbient3 +
        mDiffuse3 * LightColor * LightPower * cosTheta / (distance*distance) +
        mSpecular3 * LightColor * LightPower * pow(cosAlpha,4) / (distance*distance);
    
    color4 =
        mAmbient4 +
        mDiffuse4 * LightColor * LightPower * cosTheta / (distance*distance) +
        mSpecular4 * LightColor * LightPower * pow(cosAlpha,4) / (distance*distance);

    color5 =
        mAmbient5 +
        mDiffuse5 * LightColor * LightPower * cosTheta / (distance*distance) +
        mSpecular5 * LightColor * LightPower * pow(cosAlpha,10) / (distance*distance);
    
}