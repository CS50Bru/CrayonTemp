// STANDARD HEADER BEGINS
#version 450
#extension GL_EXT_nonuniform_qualifier : enable
// STANDARD HEADER ENDS

//DESCRIPTOR INFORMATION BEGINS
// Define our DescriptorSet inputs
layout( set = 0, binding = 0, std140 ) uniform UniformBufferObject
{
	mat4 model;
	mat4 view;
	mat4 proj;
} ubo;
layout( set = 1, binding = 0 ) uniform sampler2D texSampler[];
layout( set = 2, binding = 0, rgba8 ) readonly uniform image2D stagingImages[];
//DESCRIPTOR INFORMATION ENDS




layout(push_constant) uniform Push {
    uint frameIndex;
	float contrast;
	float brightness;
	float saturation;
} push;



layout( location = 0 ) out vec4 outColor;

vec3 linearToSRGB(vec3 linear) {
    return mix(linear * 12.92, 1.055 * pow(linear, vec3(1.0/2.4)) - 0.055, 
               step(0.0031308, linear));
}

void main()
{
	ivec2 texelCoord= ivec2(gl_FragCoord.xy);

	vec4 color=imageLoad(stagingImages[push.frameIndex], texelCoord);


	vec3 rgbColor= color.rgb;
	//rgbColor = push.contrast * (rgbColor - 0.5) + 0.5 +push.brightness;
	//rgbColor = linearToSRGB(rgbColor);
	rgbColor= clamp(rgbColor, 0.0, 1.0);
	outColor= vec4(rgbColor, color.a);
	//outColor= vec4(1.0, 1.0, 0.0, 1.0);
}

