clear all

wmremove();

%read trajectories from file in float and so on
fileID = fopen('nums1.txt','r');
sizeA = [2 Inf];
formatSpec = '%f %f';
A=fscanf(fileID,formatSpec,sizeA);
fclose(fileID);
%then putting it in two row vectors
B=A';
L=length(B);
Lat=B(1:L);
Long=B(L+1:end);
%test initialize coordinates matrix
%lat = [30.086179922289784 30.08375812841175  30.079179099142745];
%long = [31.335412434388285 31.340769430551084 31.339726989069494];

%using webmap plotting
wmline(Lat, Long);
