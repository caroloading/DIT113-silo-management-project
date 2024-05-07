package group1.silowebapp.model;

import jakarta.persistence.*;

@Entity
public class Temperature {
    
    /* Define the Object Relational Mapping (ORM). JPA/Hibernate converts 
     * the definitions to the appropriate SQL DDL statements
     */
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;

    @Column(nullable = false)
    private Double tValue;

    @Column(nullable = false)
    private String dateTime;

    @ManyToOne
    @JoinColumn(name = "silo_id")
    private Silo silo;

    protected Temperature() {
    }

    public Temperature(Double tValue, String dateTime, Silo silo) {
        this.tValue = tValue;
        this.dateTime = dateTime;
        this.silo = silo;
    }

    public Long getId() {
        return id;
    }

    public Double getTValue() {
        return tValue;
    }

    public String getDateTime() {
        // Todo: format dateTime
        return dateTime;
    }

    public Silo getSilo() {
        return silo;
    }

    @Override
    public String toString() {
        return String.format("Temperature[id=%d, value='%.2f', dateTime='%s']", id, tValue, dateTime);
    }
}
