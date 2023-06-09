#include "rayTracer.hpp"

Image RayTracer::takePicture(Scene &scene, int camIndex)
{
    Image output;
    Camera cam = (*scene.cameras[camIndex]);
    output.width = cam.width;
    output.height = cam.height;
    for (int i = 0; i < output.width; i++)
    {
        for (int j = 0; j < output.height; j++)
        {
            Color c;
            output.pixels.push_back(c);
        }
    }

    //Start at the top right corner. Go left to right, top to bottom
    for (int j = (cam.height - 1); j >= 0; j--)
    {
        for (int i = 0; i < (cam.width); i++)
        {
            ray eyeRay = cam.getEyeRay(i + .5, j + .5);

            Hit hit;
            hit = this->traceRay(scene, eyeRay, hit, 0);

            Color c = output.getPixel(i, j);
            c.r += hit.color.r;
            c.g += hit.color.g;
            c.b += hit.color.b;

            //normal map
            c.r += (hit.normal.x + 1)/2;
            c.g += (hit.normal.y + 1)/2;
            c.b += (hit.normal.z + 1)/2;

            output.setPixel(i, j, c);
        }
    }

    return output;
}

Hit RayTracer::traceRay(Scene &scene, ray &eyeRay, Hit &hit, int depth)
{
    Hit closest = hit;
    for (Geometry *item : scene.items)
    {
        Hit current = item->trace(eyeRay);
        if (current.t < closest.t)
        {
            closest = current;
        }
    }
    return closest;
}