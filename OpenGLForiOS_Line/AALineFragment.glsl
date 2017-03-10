varying mediump vec2 texCoord_f;
uniform sampler2D texUnit;

uniform lowp vec4 color;

void main()
{
    lowp vec4 fragColor = color;
    fragColor.a *= texture2D(texUnit, texCoord_f).a;
    gl_FragColor = fragColor;
}
