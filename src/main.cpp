#include "../header/context.h"
#include "../header/renderer.h"
#include "../header/camera.h"
#include "../header/input.h"
#include "../header/entity.h"
#include "../header/types.h"
#include "../header/plcli.h"
#include "../header/frame_buffer.h"
#include <utility>
#include <cstdlib>
                                                        #include "../external/stb/stb_image_write.h"
int main() {
    plContext PlContext;
    plFrame_buffer PlFrame_buffer(&PlContext);
    plRenderer PlRenderer(&PlContext, &PlFrame_buffer);
    plCamera PlCamera(&PlContext);
    plInput PlInput(&PlContext);
    plCli PlCli(&PlContext);
    PlFrame_buffer.initialize_framebuffer(
        PlContext.screen_width,
        PlContext.screen_height
    );
    Entity cube(pl::cube_vertices, pl::cube_indices, true, false);
    cube.mesh.rgb_vertices = pl::rgb::cube_sample_color_orange;
    PlRenderer.generate_buffers(cube);
    PlRenderer.generate_objects(cube);
    cube.model.offset = glm::vec3(2.0, -0.8, -3.0);
    cube.model.rotation.y = 22;

    cube.material.set_material(
        ambient(1.0f, 0.5f, 0.31f),
        diffuse(1.0f, 0.5f, 0.31f),
        specular(0.5f, 0.5f, 0.5f),
        256.0f
    );

    Entity light(pl::cube_vertices, pl::cube_indices, true, true);
    light.is_simple = true;
    light.mesh.rgb_vertices = pl::rgb::cube_sample_color_white;
    light.model.offset = glm::vec3(0.0, 0.5, -2.5);
    light.model.scale = 0.5f;
    light.model.rotation.y = 4;
    PlRenderer.generate_buffers(light);
    PlRenderer.generate_objects(light);
    
    GLuint cube_shader;
	PlRenderer.generate_shader(
        cube_shader,
        "./shaders/v_simple_sample.glsl",
        "./shaders/f_simple_sample.glsl"
    );

    GLuint light_shader;
	PlRenderer.generate_shader(
        light_shader,
        "./shaders/v_simple_sample.glsl",
        "./shaders/f_simple_light_sample.glsl"
    );

    std::vector<std::pair<Entity, shader>> scene;
    scene.emplace_back(cube, cube_shader);
    scene.emplace_back(light, light_shader);
                                                                                 bool captured = false;
    while (!PlContext.end) {
        PlRenderer.start_frame();
		PlInput.handle_input();
        PlRenderer.scene_render(scene);
        std::vector<unsigned char> pixels = PlFrame_buffer.capture_frame();
                                                                                if (!captured) {
                                                                                        auto pixels = PlFrame_buffer.capture_frame();

                                                                                        stbi_write_png(
                                                                                            "frame.png",
                                                                                            static_cast<int>(PlFrame_buffer.framebuffer_width),
                                                                                            static_cast<int>(PlFrame_buffer.framebuffer_height),
                                                                                            4,
                                                                                            pixels.data(),
                                                                                            static_cast<int>(PlFrame_buffer.framebuffer_width * 4)
                                                                                        );

                                                                                        captured = true;
                                                                                    }
        PlFrame_buffer.present_frame();
        PlContext.swap_window();
    }
    PlFrame_buffer.destroy_framebuffer();
	PlContext.dispose();
	return 0;
}