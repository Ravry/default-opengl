#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

uniform vec3 _CameraPosition;
uniform float _Time;
uniform mat4 _CameraViewMatrix;
uniform mat4 _CameraProjectionMatrix;

float sdSphere(vec3 p, float radius) {
    return length(p) - radius;
}

vec3 calculateNormal(vec3 p) {
    float d = sdSphere(p, 1.0);
    float eps = 0.001;
    vec3 n = vec3(
        sdSphere(p + vec3(eps, 0, 0), 1.0) - d,
        sdSphere(p + vec3(0, eps, 0), 1.0) - d,
        sdSphere(p + vec3(0, 0, eps), 1.0) - d
    );
    return normalize(n);
}

void main()
{
    vec2 ndc = TexCoords * 2.0 - 1.0;
    vec4 clipSpacePos = vec4(ndc, -1.0, 1.0);

    vec4 viewSpacePos = inverse(_CameraProjectionMatrix) * clipSpacePos;
    viewSpacePos /= viewSpacePos.w;

    vec3 rayOrigin = _CameraPosition;
    vec3 rayDirection = normalize((inverse(_CameraViewMatrix) * vec4(viewSpacePos.xyz, 0.0)).xyz);

    float dist = 0.0;
    vec3 p = rayOrigin;
    for (int i = 0; i < 100; i++) {
        p = rayOrigin + dist * rayDirection;
        float d = sdSphere(p, 1.0);
        if (d < 0.001) {
            vec3 normal = calculateNormal(p);

            vec3 lightDir = normalize(vec3(1, 1, -1));
            
            float diffuse = max(dot(normal, lightDir), 0.1);
            
            vec3 baseColor = vec3(0.2, 0.2, 0.8);
            vec3 litColor = baseColor * diffuse;
            
            FragColor = vec4(litColor, 1.0);
            return;
        }
        dist += d;
    }

    FragColor = vec4(.12, .12, .12, 1.0);
}