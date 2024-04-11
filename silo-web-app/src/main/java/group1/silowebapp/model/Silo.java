package group1.silowebapp.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class Silo {
    /* Define the ORM. JPA/Hibernate converts the definitions to the  
     * appropriate SQL DDL statements
     */
    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;

    @Column(nullable=false)
    private Double radius;

    @Column(nullable=false)
    private Double height;

    protected Silo() {}

    public Silo(Double height, Double radius) {
        this.height = height;
        this.radius = radius;
    }

    public Long getId() {
        return id;
    }

    public Double getHeight() {
        return height;
    }

    public void setHeight(Double height) {
        this.height = height;
    }

    public Double getRadius() {
        return radius;
    }

    public void setRadius(Double radius) {
        this.radius = radius;
    }

    @Override
    public String toString() {
        return String.format("Silo[id=%d, height='%.2f', radius='%.2f']", id, height, radius);
    }
    

}
