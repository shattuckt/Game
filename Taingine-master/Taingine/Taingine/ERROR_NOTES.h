//The purpose of this file is to take notes of all errors and fixes for them... a FAQ
/*
//PUSHING TO MY BRANCH:
git add .
git commit
git push origin branch_name
git checkout origin master
git pull origin your_branch_name
git push master
git checkout -b your_branch_name

//GENERAL RENDERING ARCHITECTURE:
Create a shader object - see any shader in this program - ShaderProgram is the parent
Initialize the shaders - loading up the shaders, binding the attributes needed, then getting the locations of the uniform variables needed for those shaders
Initialize the renderer for that object..this will:
Construct a shader in the renderer from the one created previously
Loads up any additional textures (if you create the object dynamically)
loads up the projectionMatrix
Create any entities you want to be renderered... (or update the list you already have)
Now the following is called EVERY FRAME:
Bind the FBO you want rendered (if applicible)
MasterRenderer: Render the scene:
First it will process all entities/objects for the scene (since it has to be cleared each frame)
Then we enable the clearColor
Start the shader again
load all uniform variables newly updated (or not you still gotta load them)
Specific Entity Renderer: Render
This will go through all the entities stored for this frame
It will first bind the texturedModel associated with the entity of concern
Then, it will create an batch of entities for the entity type of concern (which is a batch of entities btw)
for each entity, an object will be contructed for it
Then, the entity is sent so a new transformation matrix can be created for it (for the objects scale, rotation, position, etc)
load up the new transformation matrix for the shader
load the offset for the shader for that entity's atlas texture.. if any (its if one texture has like 4 textures inside of it)
Finally, it will actually draw the elements/arrays
Then it will unbind the texturedModel
So enable/disable any gl features you may have disabled/enabled for this renderer
disable the vertexattribarray you were using
unbind the vertexarray
Finally, stop the shader you started to render everything
clear out the entities loaded in for this frame
do it all again next frame

*******************ROOT SOURCE OF INCLUDE DIRECTORIES**************************************************
#include <vector>       = TextureData
#include <glad/glad.h>  = TextureData, RawModel, DisplayManager
#include <GLFW/glfw3.h> = TextureData, RawModel, DisplayManager
#include "stb_image.h"  = TextureData
#include <iostream>     = TextureData, DisplayManager
#include <string>       = getPaths
#include <Windows.h>    = Loader
#include "RawModel"     = Several classes - end of chain
#include <glm-0.9.8.5\glm\glm.hpp>                    = Maths
#include <glm-0.9.8.5\glm\gtc\matrix_transform.hpp>   = Maths
#include <glm-0.9.8.5\glm\gtx\string_cast.hpp>        = Maths
#include "TerrainTexture.h"                        = TerrainTexturePack
#include "ModelTexture.h"                        = TexturedModel
#include <time.h>                             = DisplayManager
#include <ctime>                              = DisplayManager


Error: Unresolved Externals
Fix: The referenced library or include might be incorrect. The glad.c file will NOT work from being downloaded, but will work if pulled from github.
Fix: make sure the cpp functions actually have the class name (ex: classname::function) you stupid shit.
Fix: Can't use non-pointer object references when using circle dependencies. GUIText.h is a perfect example (FontType* font instead of FontType font)

Error: MasterRenderer was not loading the model.
Fix: Had to declare a newRenderer and then set it to the private variable in the header file...

Error: Nothing is showing up when the game runs. Models are missing. Normal Mapped and no mapping. Along with particles.
Fix:

Error: Textures not loading correctly. They are being loaded but not mapped to the correct positions.
FIX: Its possible the picture itself gets corrupted upon transit. This has happened to multiple textures. Make sure to check a couple coordinates using the loop found at the bottom of the meshloader before
coming to this conclusion...

Error: Things aren't rendering in the distance
Fix: Change the FAR_PLANE in the master renderer to the desired render distance.

Error: Cos and Sin returning wrong values
FIX: it expects degrees.. .not radians

//ISSUES WITH NEWLY IMPLEMENTED SHADER CLASSES
1. Make sure that you implement a '[shadername]s' class that calls bindattributes and getalluniformlocations
2. make sure you both create the shader object - and then call the [shadername]s class. or else the shape wont be anything but white.

//EVERYTHING IS BLACK OR WITHOUT ANY LIGHT
1. It was an issue with the loader class - not sure what though...

Error: Skybox not loading, doesnt appear to be loading the quad either...
Fix: WOW. So make sure your stupid shader location variable names are correct and that you are using the correct locations
for the correct STUPID variables. WOWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

Error: Second cubemap throws error when attempting to bind it to openGL cubemap storage... even though the texture appears to be loading correctly
FIx: At the moment, the issue is simply the textures. LearnOpenGL's map, which is 2048x2048, worked fine with the 1024x1024 texture from thinmatrix.
NOTE: It does seem that whenever it becomes copied over, the amount of space it takes increases by 8 bytes, not sure why.

Issue: Game is running slow
FIx: its probably the terrain.
}

Issue: Could not save textures into the 2Dtexture function - only would take direct input from stbi_load data
unsigned char *testTexture;
char *textureTypeconv = (char*)(data.getTexture()); //first convert the unsigned char to char
size_t sizeofTexture = strlen(textureTypeconv); //then get the length of the char (doesnt take unsigned char)
testTexture = (unsigned char*)malloc(sizeofTexture); //Then initialize the location of the new variable to the correct size
memcpy(testTexture, data.getTexture(), sizeofTexture); //Thenc copy over the contents
Fix: Turns out vectors work since they are in a constant stream of data. So, all i needed to do this whole time was simply copy the texture data over to the vector with size (width * height * numchannels (ex; rgb  = 3))...

Error: Access violation after using pointers..
Fix: make sure your constructors actually copy the contructors. or that the object has actually been created and it isnt looking at nothing.

Error: Quad or other objects not loading
Fix 1: Thin Matrix isn't very consistent with how he handles x, y, z coordinates. In the water tutorial, he used y, x, z coordinates (which
I didnt catch initially since the program wont crash if some coordinates are switched. I believe this might
be the reason some textures are not formatted correctly when exported in blender (i think different settings than what thin matrix used need to be looked into)
Fix 2: Shader name is incorrect (like the uniform location variables)
Also the attribute names might be incorrect (this is the output of the shader so it needs to be the same)

Error: Strange errors involved with contructors or intializing private variables to other class objects
FIX: Likely a header issue where you have some header referencing back and forth. This causes errors

Error: Location variables having issues such as location being -1
FIX: Make sure you are using its own vertex/fragment shader file AND have the names spelled correctly. Shader initializes first and then you load the locations from the shader.

Error: Shader being shared between two types (in this case the normalmappingshader was using the staticshader's shader (so vertexShader and fragmentShader)
FIX: In this case I was actually sending the entities to the incorrect processor. so there one for terrain, entities, and normalmappedentities. i wasnt using the normalmappedentities one. lol. fuck me. Days to fix: 2

Error: Normal mapping is all blotchy and doesnt really match at all what it is supposed to look like
Fix: Go fuck yourself.


*/



/*//**********************************************OTHER NOTES *************************************************************************************

*******************CLIPPING PLANES*******************
The whole point of the clip distance vaiable is to tell open gl how far from the clippinng plane a vertex is.
if a distance is positive, then the object wont get culled.
so we basically get the distance of each vertex (how far it is from the clipping plane)
if the distance is negative, then the vertex is on the outside of the plane, so it is culled (not rendered)

In terms of code. You will create these horizontal planes. Take glm::vec4(0, -1, 0, 15), for example. -1 means everything above whatever height (the 4th variable.. 15) will not be rendered.
// 1 would mean everything BELOW whatever height would not be rendered.
NOTE: Using glm::vec4(0, 0, 0, 0) in the render method for the clipping planes will render EVERYTHING. THis is helpful for the main render when you dont usually want to cull anything.

Although its not optimal to render the same scene three times, it is needed to make good graphics. Using these clipping
planes will help a lot with making the game run smoother, especially for the refraction render pass because
there's usually hardly anything to render under the water. On top of that, you don't have to render the scene in
full quality when you do the reflection and refraction render passes. You can set the resolution of the frame
buffers to be lower which will make a lot of difference, and you could only render larger objects and not bother
with rendering small things like grass (the only downfall being that the grass wouldn't be reflected or seen
underwater, but that might not be a problem depending on you game).

You can also use lower res textures for the reflection pass and it won't be noticeable because the reflection
will probably be very distorted, and you can also use completely different, low quality shader programs when
rendering the reflection and refraction textures (using per vertex instead of per pixel lighting for example
So there are loads of optimizations that can be done to make sure that it is as efficient as possible


**********************DuDv Maps ********************************
DuDv maps allow for us to create dynamic distortion values for each pixel in an object
Each pixel in the map represents a 2D vector - predefined for each color (usually red/green blends)
This is used just like the multitexturing map and height map where it is sampled for each pixel on an object.

The Red/Green values will always be positive in this texture - which is an issue since we want positive and negative distortions
In order to do this, we must alter the values a bit before we can use them
Its pretty easy, all values of color are stored as values between 0 - 1 as it is.
So all we need to do is multiply the value by 2 and subtract 1.
Once this is done, we also need to implement a way to control how much distortion there is
In the waterFragment, wavestrenth allows us to specify hwo much distortion we want
However, even after all of this, there is yet another problem:
On the edges of your screen you will notice the water will have this sort of wavey border
this is due to projection texturing - the reflection and refraction texture coordinates at the bottom of the screen
will have a Y value of almost zero. AND because the distortion adds an offset to the texture coordinates, there sometimes
go BELOW zero. This will cause the texture to go off the bottom of the actual texture and will therefore wrap back around to the top of the texture
(this is due to how openGL tiles textures)
TO FIX THIS: We need to clamp the texture coordinates so they cant go too high or too low in the WaterFragment
Notice: we have to clamp the reflect coords seperately (X,Y) - this is because we flipped the Y coordinates for the reflect (they are pointing down)
Finally, the water is not rippling - which is obviously not very realistic
TO FIX THIS: We must add a moveFactor which we will change per frame
NOTE: I DID NOT IMPLEMENT THIS YET _ LEFT OFF AT 9:28 in video.
Reason being that we need to pass a pointer into the waterFragment and I'd rather test the
current version to make sure the program is still working properly before making this change...

**************** Fresnel Effect ********************************************8
The Fresnel Effect allows for the effect of dynamic transparency
For example, in water, if you are directly above it, you should be able to see the ground under it
However, if you are standing at an angle from the water, it should not be reflective at all
In other words, above water = transparent, next to water = reflective
If both the surface normal vector of the water and the camera is in the same direction, they would both be pointing up
furthermore, if the two vectors are pointed in different directions, the texture shoudl be more reflective
NOTE: Remember that the DOT product of two vectors pointing in the same direction is 1
and is equal to 0 when the vectors are perpendicular to each other



*************** Normal Mapping ******************************************
Adding normal mapping allows you to add highlights onto the water using a normal map image as a reference
This works similar to the DuDv map - each RGB value on the map represents a X,Y,Z normal vector
NOTE: The map is mostly blue because the B factor of RGB is the Y-axis. Red = X and Green = Z
Same as before, no colors can be negative, so, if nothing is done, all your normals woudl be positive.
ALthough this is fine for the Y-Axis, its not really fine for the X and Z vectors...
So... again.. we will apply the same formula on the X and Z vectors: X or Z * 2 - 1
Remember... the vectors are normalized so they are always between -1 and 1..


Once we do all of this, we then need to add the light to the world.
This was done by creating uniform variables for the vec3 light colour (RGB) and the vec3 light position (waterVertex)
Load up the variables in the waterShader (same song and dance)
Load up the variable in the waterRenderer
Since we now needed the sun we needed to pass it is as a parameter to the WaterRenderer::render method
The complicated part happens in the specular lighting
We first need to reflect the fromLightVector on the normal vector of that pixel (so a direct opposite vector leaving the vertex at the same angle but on the other side of the normal vector)
REMEMBER: the viewVector is the vector from the water to the Camera.
So, we then take the DOT product of the two vectors (viewVector and reflective) to find out how close to 1 or 0 it is
Remember, if it is closer to 1, that means the vectors are closer to the same (so the brighter the light)
If it is closer to 0, that means the vectors are farther apart. (so darker)


***************************** Soft Edges ************************
If you remember, the depth texture was renderered to a custom FBO for the refraction texture
The depth texture contains information about how far under the water the ground or any object is from the camera
So, for any fragment on the water, the depth texture can give us the distance from that fragment to the ground from the camera's angle
There is also an OpenGL built-in variable called gl_fragCoord which contains the window relative coordinate of the current fragment
the Z component of this variable gives us the depth of that fragment (meaning the distance from the camera to that fragment)
Finally, if we subtract the depth texture distance and the gl_FragCoord distance
We will obtain the distance between the current fragment and the nearest object under it (from the camera's angle)
in other words, the amount of water between the fragment and the object under it
this will be used to add all the depth effects we want on the water...

In the waterFragment, I noted where the softEdges code is
The value depth will actually not give us a depth at all and instead gives us a value between 0 and 1 representing the distance
this value is not linear, it gives much more depth perception to objects closer to the scene
we need to convert this depth value into a distance
so, we added a near and far value that is idential to the NEAR_PLANE & FAR_PLANE variables in the master renderer
NOTE: These really should be UNIFORM variables - MAKE THIS CHANGE LATER!!!
He doesnt explain how the floorDistance math works, but there are links in the video to read up on it
Ultimately, floorDistance is the distance between the camera and the floor (under the fragment)
The distance between the camera and the fragment is found using FragCoord as we said abaove.
again, that math calculation is used to deduce that distance variable
then we just subtract those two numbers to get the distance from the fragment to the floor (i get that math thankfully...)


//***************NOTE: THE FOLLOWING IS NOT RELATED TO WATER (DIRECTLY..)

****************************LIGHTS ***********************************************

*************************Attenuation factor
Attenuation impacts the brightness of a light. In our lights contructor, the higher the attenuation factor is, the dimmer the light.
The equation is as follows:
attenuation factor = (attentuation1) + (attenuation2 x d) + (attenuation3 x d^2)
NOTE: There are THREE factors but that is NOT related to X,Y,Z coordinates. in the code they are simply stored as vectors but are not related to XYZ coordinates
Where d = distance from light
As you can see, the further away you get from the light source, the higher the attenuation
You choose the three valeus of attenutation
NOTES: Setting attenuation to vec3(1.0f, 0.0f, 0.0f) means the light has no limits and never fades (which isnt realistic)
setting it to vec3(1.0f, 0.01f, 0.0f) makes the light visible for around 4 character lengths or so
Make sure whatever you do, you go in a descending order - make sure the last element is greater than 0. it gives light edges after all.

*************************** Cel Shading *********************************************************
Instead of having a surface that gradually changes from dark to light based on lighting,
Cel Shading makes distinct sections of brightness based on levels of surface brightness
This tutorial uses 4 levels of surface brightness.
This is implemented in the fragement shader: (fragmentShader)
We first need to declare the number of levels we want objects to have - 'levels'
We then need to cap the brightness variable (which is a value between 0 and 1)
To do this, we first need to find which section the brightness is currently in (by multiplying by the number of levels)
Then we floor that value... so 0.4 * 3 (three levels) = 1.2 -> floor = 1. So that falls in the second brightness level
Finally, since we need a value between 0 and 1, we divide by the number of levels. 1/3 = 0.333





//***********************NORMAL MAPPING *********************************************************
//In this engine, we can choose if we want models to load with normal mapping or not. Therefore you are not required to use models with normal mapping...

Normal mapping allows you to create fake normals onto something that has no real edges. This allows you to create high definition textured models without having to use too many resources for creating the models
We have already kinda done this in the water tutorial. Each pixel on a normal map indicates where the vector is pointing (represented in RGB)
These RGB values are all between 0 and 1, allowing us to then apply a simple conversion ((R/G/B) x 2) - 1) which gives us a value between -1 and 1
These new values are then used for our normal vectors.
However, there are some implications into implementing this
You cannot simply sample the normal map in the fragment shader and use that number in the lighting calculation
This is because the normal mapping is done in TANGENT SPACE
Our usual normal vectors are represented in world space, where 'UP' is pointing in parallel with the Y-Axis
TANGENT SPACE means all normal vectors on a FACE in the NORMAL MAP represent 'UP' as the FACE's ORIGINAL Normal Vector.
Meaning ALL normal vectors on a shape start where the face originally faced.

All of our normal lighting calculations are done in WORLD SPACE	where the camera and light positions are all in position relative to the WORLD.
As you might guess, all lighting calculations have to be done in the same space.
In order to do this, we will be converting all of the WORLD SPACE calculations into TANGENT SPACE
Then, we can do all of our calculations in TANGENT SPACE without having to change any of the normals
Converting the normals would have to be done in the fragmentShader.

***CAMERA AND LIGHT DIRECTIONS CAN BE TRANSFORMED IN THE VERTEXSHADER***
So, in order to convert these two directiosn into TANGENT space, we first need to create a matrix that can transform vectors into TANGENT space
To do this, we need three vectors to define the tangent space: the up (Z), forward (Y), and right (X) vectors
Remember, the up vector (Z) of any normal will be pointing straight out from the face
However, the forward (Y) and right (X) vectors can be pointing anywhere as long as they are perpendicular to each other and also perpendicular to the up (Z) direction
NOTE: No matter what directions are chosen, they NEED TO BE CONSISTENT WITH THE DIRECTIONS OF THE NEIGHBORING FACES to avoid ugly edges
A method of doing this would be to align them with the UV texture coordinates of the model
These other vectors are the Bi-tangent (Y) and the Tangent (X)
In order to actually get these UV new tangents, though, we need to do the following:
Calculate the tangent based on the UV texture coordinates when the model is originally loaded
Store these tangents inside the model's VAO (just like the positions, textureCoordinates, and normals..)
These will get passed to the vertex shader as a vec3 tangent variable.
Finally, the bi-tangent can be calculated by crossing the normals with the model tangents
Now that we have the bi-tangent vector, we can then create the matrix using a mat3 toTangentSpace variable..
This will be used to apply the transformation to the toCameraVector and toLightVector variables

***TRANSFORMATIONS HAVE BEEN APPLIED - FRAGMENT SHADER***
After the transformations have been applied, we just sample the normal map with the textureCoordinates
All lighting calculations must then be done in TANGENT space.

Before any of the above can be done, we need to actually calculate the tangent vectors for each vertex using a NEW object loader.
The following equation is used:
For a given triangle with vertex positions P0, P1, P2 and corresponding UV texture coords T0, T1, and T2:
deltaPos1 = P1 - P0
deltaPos2 = P2 - P0
deltaUV1  = T1 - T0
deltaUV2  = T2 - T0

r = 1 / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x)

tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r



***********************************************Font Rendering****************************************************
This will be implemented using a texture atlas, which is essentially a picture that contains all the letters inside of it.
However, each character has a special set of coordinates it needs to use in order to extract the characters and place it accordingly.
	This is called a 'font file' which contains all of the texture atlas properties for each character
		each line contains info about each character.
		ID is the ASCII character ID.
		the X and Y fields indicate the TOP LEFT corner if the character's location inside the texture atlas
		the width and height are simply the dimensions of that character

Just with this information, we coudl already render a letter wherever we wanted. However, we still wouldnt know how much offset each character would need in relation to what was already written
	We will solve this by using a virtual line to track where we are placing text

		This is where the xoffset and yoffset values in the font file come into play. They tell us where the character should be rendered in relation to this virtual cursor we will be using.
		The xadvance value is how far to the right we shoudl then move our cursor after the selected character has been rendered.
PART 2:
In order to add effects to our text, we use signed distance fields.
	This tells us how far from the center of the letter a pixel is. Meaning a pixel on the far edge of a letter
		would be more opaque where a pixel closer to the center would be solid.
NOTE: This also allows us to scale text while still retaining clarity. The old method would render very pixelated letters.

How to Use Hiero v5:
	Select the font you want and set padding to 8 with x/y to 0. (SELECT JAVA FOR RENDERING)
	Select 'glyph cache' and scale the size up until you are as high as possible without going to two pages
	Use effect of 'distance field' and remove the solid color one
	Set the scale to 10 and set scale to 15 (although you can set it to highe rif you want)
	save as bmfont.


For sin distance fields, we have to choose a value for how far from the center we want characters to be rendered.
we also need an edge width field so that we can smooth the edges a bit

any pixel with an alplha value of 1 will mean solid color.
any pixel with an alpha value of 0 will mean its completely outside the character and should be clear.
any pixel with any other alpha value would be the edge, since you want a gradient from 1 to 0 to smooth the edges.

glsl has a function called 'smoothstep' which basically does the edge calculations
	smoothstep(edge0, edge1, x);
		any value less than edge0 returns 0
		any value greater than edge1 returns 1
		any value between edge0 and edge1 will return a value between 0 and 1 depending on its location
	Might have noticed already, but this returns the opposite values that we want so we need to do 1-smoothstep so that 1 is solid and 0 is transparent

NOTE: for LARGER font sizes, you would want to use a lower edge value and higher width value
		so smaller you would want higher edge value but lower width value

Special effects for text are created through the border variables. These act just like the edge and width values.
hard border: borderWidth = 0.7 & borderEdge = 0.1
'glowing' border: borderWidth = 0.4 & borderEdge = 0.5
	This is basically forcing the transition to be much larger.

Offset, which is the drop shadow, can be done as well.
	note: offsets cause some wierd rendering due to the meshes being moved. they can overlap and cause lines to show that shouldnt be there
		only fix is to just tweak it as you go, lower the padding, change the offset amount, the border width, etc.
		main fix for the lines is to add more padding in heiro when creating the atlas..

	To remove ALL border effects, simply set the borderWidth to 0.

********************************************************************************************************************************
********************************************************************************************************************************
PARTICLE EFFECTS:
PART 1: QUAD PARTICLE EFFECTS
A particle is defined by its position, velocity, gravityEffect, and lifeLength:
	Velocity being a vector dictating the speed and direction it is traveling.
	gravityEffect is how much that particle is effected by gravity, closer to zero means less gravity
	lifeLength is the duration of the particle's life

All the magic happens in the updateModelViewMatrix method.
	Without this transformation, the quads would always face their original orientation
	Which means we could see them from the side which would make the dissapear from the camera's view
	So basically we are updating the models to ALWAYS face the camera no matter where the camera is pointed
	This can be done by the following:
		View Matrix * Model Matrix = ModelView Matrix WITHOUT ANY ROTATION. The rotation of a modelMatrix is the top left 3x3 box, so 00,01,02,10,11,12,20,21,22. The bottom row and right column do not need to be altered.. 
			IN order to prevent rotation from happening, we need update the matrix to the following:
			{   M0-0   M1-0   M2-0   M3-0
				M0-1   M1-1   M2-1   M3-1
				M0-2   M1-2   M2-2   M3-2
				M0-3   M1-3   M2-3   M3-3   }

			Setting the following bits to static will prevent rotation:
			{    1      0      0     M3-0
				 0      1      0     M3-1
				 0      0      1     M3-2
			   M0-3   M1-3    M2-3   M3-3   }

			What is happening here is that, instead of multiplying, we are transposing the rotation of the viewMatrix
		1	        VIEW MATRIX                                 MODEL MATRIX
			{   M0-0   M1-0   M2-0   M3-0              {   M0-0   M1-0   M2-0   M3-0
				M0-1   M1-1   M2-1   M3-1                  M0-1   M1-1   M2-1   M3-1
				M0-2   M1-2   M2-2   M3-2         X        M0-2   M1-2   M2-2   M3-2
				M0-3   M1-3   M2-3   M3-3   }              M0-3   M1-3   M2-3   M3-3   }

		2		    VIEW MATRIX                                 MODEL MATRIX
			{    A       B     C     M3-0              {    A       D     G     M3-0
				 D       E     F     M3-1                   B       E     H     M3-1
				 G       H     I     M3-2         X         C       F     I     M3-2
				M0-3   M1-3   M2-3   M3-3   }              M0-3   M1-3   M2-3   M3-3   }
			all that is happening here is the model matrix gets set to the vars from the viewMatrix.
			However, muliplying is either a 1 or a 0 here, and its 1 where the letters are alike and 0 where they are not
			Meaning this is the final modelViewMatrix:
			{    1      0      0     M3-0
				 0      1      0     M3-1
				 0      0      1     M3-2
			   M0-3   M1-3    M2-3   M3-3   }

PART 2 - Texturing the Particles
The life of a particle will indicate with part of a texture atlas to use. Each stage of life having a different texture to use.
ParticleTexture class is used to store the textureID and numberOfRows that particle's texture has.
ParticleMaster in his example uses an addParticle4 method.

Without using the depth buffer, the newest particle in the system would be rendered on top even if there are hundreds of other particles that are supposed to be rendered in front of it.
	however, activating the depth buffer doesnt take transparency into account and therefore you will have quad shaped particles with your texture in the middle of the boxes. The boxes only being visible because of
		the depth buffer basically seeing a texture is there, and decides to render it, which makes any particle behind it either not show at all or pokes around the sides. 
	One solution to this is to correctly order how the particles are being rendered while NOT using the depth buffer.
		Particles rendered FIRST will be rendered in the back, while particles rendered LAST will be rendered at the front.6

	Another solution is to use additive blending, which really is only good when you want the particles to look rather glowing (such as magic effects)
		This is easily done by changing the glBlendFunc in the prepare method from 'GL_ONE_MINUS_SRC_ALPHA' to 'GL_ONE'

Animating the textures requires using the lifespan parameter
	using the updateTextureCoordInfo method, we update the atlasProgression variable to indicate which texture to use
		example: 5.6 on a 4x4 atlas would use the second element of the second row
			the 0.6 is an indicator of how close the particle is into the next stage (or tile i guess) 
			we can utilize this as a 'blend' factor. Texoffset2 is actually the next stage where texoffset1 is the current. The offset is defined from the blend factor. The higher the blend value, the more it looks like the next stage.. vise versa.

So ultimately, this version uses multiple particleSystems to list out different instances of particle effects. 
There is a large issue on sorting these so that they are rendered correctly when sorting. 
	If you simply use them as-is with no sorting, particles will all render as if they are equal distance away, which obviously isnt correct.
	however, if you sort them individually to simply fix the depth buffer issue, you will still have the issue of individual particleSystems rendering over each other
		tehcnically you could sort them all as one huge list, but then you would have to bind and unbind textures as you go through the list. when combining systems, this could get VERY ineffecient
	You could also sort them based on which particleSystem it is under, but when they use the same atlas, there wouldnt be a way to know which particles of that atlas list would need to be used.
	best solution according to him is to use a giant textureAtlas that has all of the different particle effects inside of it. (although I worry about the resolution of these particles.

PART 3 - Instanced Rendering
Instanced rendering essentially allows you to draw several entities/particles onto the screen with a single glDrawArray call. Currently, we use the following to draw any sort of entity:
	glDrawArrays(GL_TRIANGLE_STRIP, vertexCount) where GL_TRIANGLE_STRIP can change a bit here and there depending on what you wanna do.
	The new method is the following:
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, vertexCount, count)
	This really only matters when rendering thousands of things a second, so... always. And will be crucial to managing performance in the future. 
There are issues with using this method of rendering, however. Since we would no longer be looping through the list, we wouldnt have any way to indicate which texture to use, where it should be rendered, or how itll move
	This is the case for anything rendered using this method, so we need a new method to update all of those things.

	One solution would be to use gl_InstanceID which is used in the vertex shader
		it will be an int that represents each instance in that count. So the first would be gl_InstanceID = 0, then 1, then 2, etc. etc. 
		The following is an example usage of this method: (it simply will render all of the particles side by side in a straight line as only the 'x' coordinate is updated.)
			uniform mat4 projectMatrix;
			uniform mat4 viewMatrix;

			uniform vec2 texOffset1;
			uniform vec2 texOffset2;
			uniform vec2 texCoordInfo;

			void main(void){

				vec2 textureCoords = position + vec2(0.5, 0.5);
				textureCoords.y = 1.0 - textureCoords.y;
				textureCoords /= texCoordInfo.x;
				textureCoords1 = textureCoords + texOffset1;
				textureCoords2 = textureCoords + texOffset2;
				blend = texCoordInfo.y;
				vec3 vertexPosition = vec3(position.x + 490.0, position.y + 10.0, -300.0);

				vertexPosition.x += gl_InstanceID; //this is the only part of the particle being updated for all of them.

				gl_Position = projectionMatrix * viewMatrix * vec4(vertexPosition, 1.0);
	
	In order to update each particle with its own info, we are going to use VAO's.
		VAO is the vertex attribute object that we used before. It simply holds all of the attribute information for a vertex.
			This is currently used for Position, Texture Coordiantes, and Normal Vectors. 
			They are acced in vertexShaders using the 'in' keyword.
				ex: in vec3 position;
			This already is used in a loop fashion in shaders. The shader will loop through all of the VAO elements to render entities
				EX: The shader's first rendering would be Pos 0, Tex Coord 0, and Normal 0. Then it would go to Pos 1, Tex Coord 1, Normal 1, etc. etc. 
			Also already used, the elements of each list in the VAO was stored using glVertexAttribPointer which we would tell the vao how many floats are used in each. 
				Exampe positions using three floats for each element of the Positions VAO where textureCoords would only have 2 floats
				Positions VAO ex:  0,2,1   -1,0,0   0,-1,2
				TextureCoords VAO: 0.5,0.5  0.1,0.8  0.2, 0.7
				Which we then rendered using the draw arrays with GL_TRIANGLE_STRIP

			This is where instanced rendering comes in. We can add additional VAO attributes with a special tag to make them instanced attributes.
				These behave differently than the traditional attributes we used as  
				So basically for 300 instances, you would need 300 world pos and colors (so instance elements)
					In other words, each instance element represents each gl_InstanceID.
						so we are rendering 300 instances of the EXACT SAME vertex data.

			In the code, we need to pass in a load more stuff into the shaders for this. 
				Positions - 2 floats (same as before)
				ModelViewMatrix - 16 floats - per instance attribute 
					limit for vao's elements are 4 floats each. So each column of the matrix will be represented as ColA,B,C, and D in the vao
						In other words, Col A, B, C and D will each have its own list (so they use different attribute list numbers)
				TextureOffset - 4 floats - per instance attribute
				Blend factor - 1 float
			Each of these have to be updated EVERY SINGLE FRAME. In order to do this effectively, we need to update only ONE VBO using interlveaing instead of having to update 6 different ones.
				We dont need to include positions into this large vbo

			This architecture is basically identical to that which is used in the learnOpenGL.com guide, where you have each entity represented as a segment in the VBO architecture:
			EX:   ColA 0,  ColB 0, ColC 0, ColD 0, TexOff 0, Blend0  //end entity/particle  then the next element after Blend0 would be ColA 1, then Colb 1, etc, etc. 
				Loading this data up is done using the same method as before, just with different params:
					Previously used: glVertexAttribPointer(attr, size, GL_FLOAT, false, 0, 0);
					Updated method will use the final two parameters.
						The first one is the STRIDE parameter
							This indicates the amount in Bytes that each particle/entity uses
								In the particle's case, this would be the same for each attribute. 
									It uses 21 floats total, or 84 bytes. 
						The second one is the OFFSET parameter
							This indicates how many bytes into each stride the data can be found
								ColA 0, ColB 0, ColC 0, ColD 0, TexOff 0, Blend 0
								  4f     4f       4f       4f      4f        1f
								So to get to TexOff 0 we would need 16 floats, or 64 bytes.
			
			Really, after the VBO is stored using this method, the vao can be treated the same as before. Where we use shaders to store the uniform variables, then access them in the shaders.
			One difference in using this VBO is that we have to use 'GL_STREAM_DRAW' instead of GL_STATIC_DRAW as we actually need to update this vbo since it will have the model view matrix calculations in it basically. 
			The only large change after that would be the new render method which would be something like this:
				render(unordered map<ParticleTexture, std::vector<Particles*>> particles, Camera camera){
					prepare();
					for (Particle texture : particles.keyset()){
						bindTexture(texutre);
						std::vector<Particle*> particeList = particles[texture];
						pointer = 0;
						for (Particle particle : particleList) {
							updateModelViewMatrix(particle.getPosition(), particle.getRotation(), particle.getScale(), viewMatrix, vboData);
							updateTexCoordInfo(particle, vboData);
						}
						loader.updateVbo(vbo, vboData);
						glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad.getVertexCount(), particleList.size());
					}
					finishRendering;
				}

		Rendering System Idea:
			Main:
				Declare RenderingSystems
				Declare ParticleMaster


******************************************PROCEDURAL TERRAIN********************************************************
The main point of this is to create heights that make the terrain look somewhat natural while also giving a quick method of getting terrain heights

Most notes are in the header files, but here is how interpolation is done:
      Generate heights is called for (x,z)
	  

	  Interpolation of (x,z):
	  Get V1, v2, v3, v4:
	  V1 (x, z)                    V2 (x + 1, z)



	  V3 (x, z + 1)                V4 (x + 1, z + 1)

	  Interpolation of V1/V2 and V3/V4 happen (notice its not center, this imaginary column can appear anywhere between V1/v2 and v3/v4...
	  V1 (x, z)       i1           V2 (x + 1, z)

			        (x,z)

	  V3 (x, z + 1)   i2         V4 (x + 1, z + 1)
      Now we can finall interpolate i1 and i2 which will simply return the height of (x,z).

	In order to actually use interpolation, we have to create more inputs (instead of just using integer coordinates.
		Reason being that interpolation only creates values for the space between these coordinates. 
		
*************************************Shadow mapping******************************************
Basically, imagine it as you are the light source. Anything you can't see should be a shadow.
		*/