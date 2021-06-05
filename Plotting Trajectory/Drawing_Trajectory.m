clear all



%read trajectories from file in form of float(latititude space longitude new line) and
%so on
%then putting it in two row vectors

%test initialize coordinates matrix
latitudes = [30.08616870922283];
longitudes = [31.33528433733129];



%latSeattle = 47.62;
%lonSeattle = -122.33;
%latAnchorage = 61.20;
%lonAnchorage = -149.9;

%geoplot([latSeattle latAnchorage],[lonSeattle lonAnchorage],'-*')
%geolimits([45 62],[-149 -123]) %customize it according to the area we're going to walk in
%geobasemap streets % or geobasemap satellite or streets-light
wmremove();
lat = [30.086179922289784 30.08375812841175  30.079179099142745];
long = [31.335412434388285 31.340769430551084 31.339726989069494];
wmline(lat, long);
