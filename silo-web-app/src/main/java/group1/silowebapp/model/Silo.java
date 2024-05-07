package group1.silowebapp.model;

import jakarta.persistence.*;

@Entity
public class Silo {
    
    /* Define the Object Relational Mapping (ORM). JPA/Hibernate converts 
     * the definitions to the appropriate SQL DDL statements
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;

    @Column(nullable = false)
    private Double radius;

    @Column(nullable = false)
    private Double height;

    @Column(nullable = false)
    private String mcuName;

    @Column(nullable = false)
    private String mcuVendor;

    @Column(nullable = false)
    private String mcuModel;

    protected Silo() {
    }

    public Silo(Double height, Double radius, String mcuName, String mcuVendor, String mcuModel) {
        this.height = height;
        this.radius = radius;
        this.mcuName = mcuName;
        this.mcuVendor = mcuVendor;
        this.mcuModel = mcuModel;
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

    public String getMcuName() {
        return mcuName;
    }

    public void settMcuName(String mcuName) {
        this.mcuName = mcuName;
    }

    public String getMcuVendor() {
        return mcuName;
    }

    public void settMcuVendor(String mcuVendor) {
        this.mcuVendor = mcuVendor;
    }

    public String getMcuModel() {
        return mcuModel;
    }

    public void settMcuModel(String mcuModel) {
        this.mcuModel = mcuModel;
    }

    @Override
    public String toString() {
        return String.format("Silo[id=%d, height='%.2f', radius='%.2f']", id, height, radius);
    }


}
