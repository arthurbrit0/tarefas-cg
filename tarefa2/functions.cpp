#include "raylib.h"
#include <iostream>
#include "header.h"

using namespace std;

const float janelaWidth = 2.0f;
const float janelaHeight = 1.5f;
const float janelaDistance = 1.0f;
const float raioEsfera = 1.0f;
const Vector3D centroEsfera(0.0f, 0.0f, -(janelaDistance + raioEsfera));
const Color corBackground = {100, 100, 100, 255};  

const int telaWidth = 800;
const int telaHeight = 600;

LightSource fonteLuz(Vector3D(0.0f, 5.0f, 0.0f), Vector3D(0.7f, 0.7f, 0.7f));

const Vector3D diffuseReflection(1.0f, 0.0f, 0.0f);  
const Vector3D specularReflection(1.0f, 1.0f, 1.0f); 
const float shininess = 32.0f;  

void renderScene(Sphere& sphere) {
    float pixelWidth = janelaWidth / telaWidth;
    float pixelHeight = janelaHeight / telaHeight;

    for (int row = 0; row < telaHeight; row++) {
        float yCoord = janelaHeight / 2.0f - pixelHeight / 2.0f - row * pixelHeight;
        for (int col = 0; col < telaWidth; col++) {
            float xCoord = -janelaWidth / 2.0f + pixelWidth / 2.0f + col * pixelWidth;

            Vector3D pixelCenter(xCoord, yCoord, -janelaDistance);
            Ray3D ray(Vector3D(0.0f, 0.0f, 0.0f), pixelCenter);

            float tHit = 1000.0f;
            if (sphere.intersect(ray, tHit)) {
                Vector3D intersectionPoint = ray.origin + ray.direction * tHit;
                Vector3D normalAtIntersection = (intersectionPoint - sphere.center).normalize();
                Vector3D viewDirection = -ray.direction.normalize();
                Vector3D lightDirection = (fonteLuz.position - intersectionPoint).normalize();
                Vector3D reflectedLight = normalAtIntersection * 2 * normalAtIntersection.dot(lightDirection) - lightDirection;

                float diffuseIntensity = max(0.0f, normalAtIntersection.dot(lightDirection));
                float specularIntensity = pow(max(0.0f, reflectedLight.dot(viewDirection)), shininess);

                Vector3D diffuseColor = diffuseReflection * fonteLuz.intensity * diffuseIntensity;
                Vector3D specularColor = specularReflection * fonteLuz.intensity * specularIntensity;
                Vector3D finalColor = diffuseColor + specularColor;

                int r = min(255, max(0, static_cast<int>(finalColor.x * 255)));
                int g = min(255, max(0, static_cast<int>(finalColor.y * 255)));
                int b = min(255, max(0, static_cast<int>(finalColor.z * 255)));

                DrawPixel(col, row, Color{(unsigned char)r, (unsigned char)g, (unsigned char)b, 255});
            }
        }
    }
}

int main() {
    InitWindow(telaWidth, telaHeight, "Raytracer");

    SetTargetFPS(60);

    Sphere sphere(centroEsfera, raioEsfera);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(corBackground);

        renderScene(sphere);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
