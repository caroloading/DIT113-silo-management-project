package group1.silowebapp.model;

import jakarta.persistence.*;

@Entity
public class GrainHeight {

    /* Define the Object Relational Mapping (ORM). JPA/Hibernate converts
     * the definitions to the appropriate SQL DDL statements
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;

    @Column(nullable = false)
    private Double height;

    @Column(nullable = false)
    private String dateTime;

    @ManyToOne
    @JoinColumn(name = "silo_id")
    private Silo silo;

    protected GrainHeight() {
    }

    public GrainHeight(Double height, String dateTime, Silo silo) {
        this.height = height;
        this.dateTime = dateTime;
        this.silo = silo;
    }

    public Long getId() {
        return id;
    }

    public Double getHeight() {
        return height;
    }

    //getting the percentage
    //as a derived attribute
    public Double getPercentage() {
        if (silo != null) {
            Double percentage = height / silo.getHeight() * (-100) + 100;
            return percentage >= 0.0 ? percentage : 0.0;
        } else {
            return -1.0;
        }
    }

    public String getDateTime() {
        return dateTime;
    }

    public Silo getSilo() {
        return silo;
    }

    public boolean isOutOfBounds() {
        return getPercentage() > 85.0;
    }

    @Override
    public String toString() {
        return String.format("GrainHeight[id=%d, value='%.2f', dateTime='%s']", id, height, dateTime);
    }
}
