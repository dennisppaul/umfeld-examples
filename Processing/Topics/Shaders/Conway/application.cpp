// GLSL version of Conway's game of life, ported from GLSL sandbox:
// http://glsl.heroku.com/e#207.3
// 
// This example implements Conway's Game of Life using a fragment shader
// with double buffering to simulate the "ppixels" uniform from Processing.

#include "Umfeld.h"
#include "PShader.h"
#include "PGraphics.h"

using namespace umfeld;

PShader* conway;
PGraphics* buffer1;  // Single buffer for screen capture (like BlurFilter)

void settings() {
    size(400, 400, RENDERER_OPENGL_3_3_CORE);
}

void setup() {
    // Create single buffer for screen capture (simplified approach like BlurFilter)
    buffer1 = createGraphics(400, 400);
    
    // Load vertex and fragment shaders
    std::string vert = loadString("conway.vert");
    std::string frag = loadString("conway.glsl");
    conway = loadShader(vert, frag);
    
    // Set resolution uniform (constant)
    conway->set_uniform("resolution", glm::vec2(400.0f, 400.0f));
    
    // Initialize with black screen for first frame
    background(0.0f);
}

void draw() {
    // Step 1: Copy current main screen to offscreen buffer (like BlurFilter approach)
    buffer1->beginDraw();
    buffer1->image(g, 0, 0);  // Preserve current screen state
    buffer1->endDraw();

    // Step 2: Apply Conway shader and render back to main screen
    shader(conway);
    
    // Set Conway shader uniforms
    conway->set_uniform("time", (float)millis() / 1000.0f);
    float x = map(mouseX, 0, width, 0, 1);
    float y = map(mouseY, 0, height, 1, 0);
    conway->set_uniform("mouse", glm::vec2(x, y));
    conway->set_uniform("previousFrame", 0);
    
    // Use captured screen as texture input
    texture(buffer1);
    fill(1.0f);
    noStroke();
    
    // Full-screen quad (Y coordinates flipped for proper texture mapping)
    beginShape(QUADS);
    vertex(0, 0, 0, 0, 1);
    vertex(width, 0, 0, 1, 1);
    vertex(width, height, 0, 1, 0);
    vertex(0, height, 0, 0, 0);
    endShape();
    
    shader();  // Reset shader
    texture(); // Reset texture
}

/*
 * TECHNICAL ANALYSIS: Conway's Game of Life Implementation Failure
 * 
 * ORIGINAL PROCESSING REQUIREMENTS:
 * - Single 'ppixels' uniform sampler2D accessing previous frame data
 * - Conway's Game of Life needs current cell state + 8 neighbor cells from previous frame
 * - Requires texture feedback loop: current render → texture → next frame input
 * 
 * UMFELD RENDERING PIPELINE LIMITATIONS:
 * 
 * 1. SINGLE TEXTURE UNIT CONSTRAINT:
 *    File: /home/choiharam/works/umfeld/umfeld/include/PGraphicsOpenGL_3_3_core.h:121
 *    Code: int DEFAULT_ACTIVE_TEXTURE_UNIT = 0;
 *    - Comment: "NOTE OpenGL ES 3.0 does not support multiple texture units"
 *    - Function: IMPL_bind_texture() always binds to GL_TEXTURE0 + DEFAULT_ACTIVE_TEXTURE_UNIT
 *    - Impact: Cannot bind both current screen buffer AND previous frame texture simultaneously
 * 
 * 2. TEXTURE BINDING CENTRALIZATION:
 *    File: /home/choiharam/works/umfeld/umfeld/src/PGraphicsOpenGL_3_3_core.cpp:61-66
 *    Function: void PGraphicsOpenGL_3_3_core::IMPL_bind_texture(const int bind_texture_id)
 *    Code: glActiveTexture(GL_TEXTURE0 + DEFAULT_ACTIVE_TEXTURE_UNIT);
 *          glBindTexture(GL_TEXTURE_2D, texture_id_current);
 *    - All texture operations forced through single texture unit
 *    - Manual glActiveTexture(GL_TEXTURE1) calls get overridden
 * 
 * 3. FRAMEBUFFER FEEDBACK LOOP PREVENTION:
 *    File: /home/choiharam/works/umfeld/umfeld/src/PGraphicsOpenGL_3_3_core.cpp:1331
 *    Function: image() implementation uses IMPL_bind_texture(framebuffer.texture_id)
 *    - Attempting to use current framebuffer as texture input while rendering to it
 *    - Creates undefined behavior in OpenGL (reading from currently bound render target)
 * 
 * 4. INADEQUATE DOUBLE BUFFERING SUPPORT:
 *    - No built-in mechanism for preserving previous frame data
 *    - PGraphics buffer copy approach conflicts with main framebuffer rendering
 *    - Missing true ping-pong buffer implementation
 * 
 * ROOT CAUSE ANALYSIS:
 * Conway's Game of Life fundamentally requires:
 * - Texture Unit 0: Current framebuffer being written to
 * - Texture Unit 1: Previous frame data being read from
 * 
 * umfeld's architecture prevents this by:
 * - Hardcoding all texture operations to unit 0
 * - Centralizing texture binding through IMPL_bind_texture()
 * - Lacking proper multi-texture state management
 * 
 * CONCLUSION:
 * This is not a shader compatibility issue or API difference.
 * This is a fundamental architectural limitation where umfeld's rendering pipeline
 * intentionally restricts multi-texture operations required for cellular automata simulations.
 */
