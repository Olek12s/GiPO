#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;  // pozycja światła
uniform vec3 viewPos;   // pozycja kamery

void main() {
    //FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);

// ambient
    float ambientStrength = 0.1f;                   // siła oświetlenia ambient
    vec3 ambient = ambientStrength * lightColor;    // kolor na podstawie koloru światła

// diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);     // iloczyn skalarny (dot product) między normalną a kierunkiem światła
    vec3 diffuse = diff * lightColor;

// specular
    float specularIntensity = 0.5f;                 // siła odblasku
    float specularShininess = 32;                   // blask odbicia
    vec3 viewDir = normalize(viewPos - FragPos);    // kierunek kamery
    vec3 reflection = reflect(-lightDir, norm);     // kierunek odbicia względem wektora normalnego powierzchni

    float specularComponent = pow(max(dot(viewDir, reflection), 0.0), specularShininess);
    vec3 specular = specularIntensity * specularComponent * lightColor;

    //vec3 result = ambient * objectColor;    // kolor światła * kolor obiektu
    //vec3 result = (ambient + diffuse) * objectColor;    // kolor światła * kolor obiektu
    vec3 result = (ambient + diffuse + specular) * objectColor;    // kolor światła * kolor obiektu

    FragColor = vec4(result, 1.0);
}