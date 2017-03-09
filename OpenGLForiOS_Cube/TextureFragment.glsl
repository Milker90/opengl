precision highp float;

varying vec2 v_texCoord;
uniform sampler2D u_samplerTexture;
uniform bool useMixColor;

void main()
{
    vec4 texColor = texture2D(u_samplerTexture, v_texCoord);
    if (useMixColor){
        gl_FragColor = texColor * vec4(1.0, 0, 0, 0.3);
    } else {
        gl_FragColor = texColor;
    }
}
