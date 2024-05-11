package group1.silowebapp;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.security.servlet.SecurityAutoConfiguration;

/*
 * The SecurityAutoConfiguration adds features such as form login that aren't needed
 * right now. Thus, exclude it.
 */

@SpringBootApplication(exclude = {SecurityAutoConfiguration.class})
public class SiloWebAppApplication {

    public static void main(String[] args) {
        SpringApplication.run(SiloWebAppApplication.class, args);
    }
}