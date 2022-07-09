#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#define SOKOL_IMPL
#define SOKOL_GLES2
#include "sokol/sokol_gfx.h"
#include "emsc.h"

static struct {
    sg_pipeline pip;
    sg_bindings bind;
    sg_pass_action pass_action;
} state = {
    .pass_action.colors[0] = { .action = SG_ACTION_CLEAR, .value = { 0.0f, 0.0f, 0.0f, 1.0f } }
};
static void draw();

int main() {
    /* setup WebGL context */
    emsc_init("#canvas", EMSC_ANTIALIAS);

    /* setup sokol_gfx */
    auto test = sg_desc{0};
    sg_setup(&test);
    assert(sg_isvalid());

    /* a vertex buffer with 3 vertices */
    const float vertices[] = {
        // positions            // colors
         0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
    };

    auto buffer_desc = (sg_buffer_desc){
            .data = SG_RANGE(vertices)
        };
    state.bind.vertex_buffers[0] = sg_make_buffer(&buffer_desc);

    /* create a shader */
    auto shader_desc = sg_shader_desc{
        .attrs = {
            [0].name = "position",
            [1].name = "color0"},
        .vs.source = "attribute vec4 position;\n"
                     "attribute vec4 color0;\n"
                     "varying vec4 color;\n"
                     "void main() {\n"
                     "  gl_Position = position;\n"
                     "  color = color0;\n"
                     "}\n",
        .fs.source = "precision mediump float;\n"
                     "varying vec4 color;\n"
                     "void main() {\n"
                     "  gl_FragColor = color;\n"
                     "}\n"};

    sg_shader shd = sg_make_shader(&(shader_desc));

    /* create a pipeline object (default render states are fine for triangle) */
    auto pipeline = sg_pipeline_desc{
        /* if the vertex layout doesn't have gaps, don't need to provide strides and offsets */
        .shader = shd,
        .layout = {
            .attrs = {
                [0].format = SG_VERTEXFORMAT_FLOAT3,
                [1].format = SG_VERTEXFORMAT_FLOAT4}},
    };

    state.pip = sg_make_pipeline(&pipeline);

    /* hand off control to browser loop */
    emscripten_set_main_loop(draw, 0, 1);
    return 0;
}

/* draw one frame */
static void draw() {
    sg_begin_default_pass(&state.pass_action, emsc_width(), emsc_height());
    sg_apply_pipeline(state.pip);
    sg_apply_bindings(&state.bind);
    sg_draw(0, 3, 1);
    sg_end_pass();
    sg_commit();
}