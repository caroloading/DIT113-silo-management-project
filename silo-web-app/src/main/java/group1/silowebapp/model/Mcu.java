package group1.silowebapp.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class Mcu {
    /* Define the ORM. JPA/Hibernate converts the definitions to the 
     * appropriate SQL DDL statements
     */
    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;

    @Column(nullable=false, unique=true)
    private String name;

    @Column(nullable=false)
    private String vendor;

    @Column(nullable=false)
    private String prodModel;

    protected Mcu() {}

    public Mcu(String name, String vendor, String prodModel) {
        this.name = name;
        this.vendor = vendor;
        this.prodModel = prodModel;
    }

    public Long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getVendor() {
        return vendor;
    }

    public void setVendor(String vendor) {
        this.vendor = vendor;
    }

    public String getProdModel() {
        return prodModel;
    }

    public void setProdModel(String prodModel) {
        this.prodModel = prodModel;
    }

    @Override
    public String toString() {
        return String.format("MCU[id=%d, name='%s', vendor='%s', prodModel='%s']", id, name, vendor, prodModel);
    }
}
