clear all

wmremove();

%read trajectories from file in float and so on
%then putting it in two row vectors

%test initialize coordinates matrix
lat = [30.086179922289784 30.08375812841175  30.079179099142745];
long = [31.335412434388285 31.340769430551084 31.339726989069494];


%using webmap plotting
wmline(lat, long);
