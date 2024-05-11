const map = new ol.Map({
    target: "map",
    layers: [
        new ol.layer.Tile({
            source: new ol.source.OSM(),
        }),
    ],
    view: new ol.View({
        center: ol.proj.fromLonLat([geoLong, geoLat]),
        zoom: 12,
    }),
})

const markers = new ol.layer.Vector({
    source: new ol.source.Vector(),
    style: new ol.style.Style({
        image: new ol.style.Icon({
            anchor: [0.5, 0.5],
            src: "../images/icons/map_marker.png",
            scale: 0.05,
        }),
    }),
});
map.addLayer(markers);

const siloMarker = new ol.Feature(
    new ol.geom.Point(ol.proj.fromLonLat([geoLong, geoLat]))
);
markers.getSource().addFeature(siloMarker);