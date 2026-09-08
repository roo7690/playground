plugins {
    id("java")
    id("application")
}

group = "inf3405"
version = "1.0.0"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(platform("org.junit:junit-bom:6.0.0"))
    testImplementation("org.junit.jupiter:junit-jupiter")
    testRuntimeOnly("org.junit.platform:junit-platform-launcher")
}

application {
    mainClass.set("client.Main")
}

tasks.jar {
    manifest {
        attributes["Main-Class"] = "client.Main"
    }
}

tasks.register<Jar>("clientJar") {
    group = "build"
    description = "Builds the executable client JAR."
    archiveBaseName.set("client")
    archiveVersion.set("")
    manifest {
        attributes["Main-Class"] = "client.Main"
    }
    from(sourceSets.main.get().output)
}

tasks.register<Jar>("serverJar") {
    group = "build"
    description = "Builds the executable server JAR."
    archiveBaseName.set("server")
    archiveVersion.set("")
    manifest {
        attributes["Main-Class"] = "server.Main"
    }
    from(sourceSets.main.get().output)
}

tasks.named("build") {
    dependsOn("clientJar", "serverJar")
}

tasks.test {
    useJUnitPlatform()
}
