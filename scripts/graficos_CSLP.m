clc;
clear;
close;

% Specify the file name
filename = 'data.csv';

% Read the CSV file
data = readtable(filename);

% Extract columns into lists
name = table2cell(data(:,1));
blockSize = table2array(data(:,2));
searchArea = table2array(data(:,3));
keyframePeriod = table2array(data(:,4));
quantizationY = table2array(data(:,5));
quantizationU = table2array(data(:,6));
quantizationV = table2array(data(:,7));
executionTime = table2array(data(:,8));
PSNR = table2array(data(:,9));
PSNR(PSNR == inf) = 65;
compressionRatio = table2array(data(:,10));

name = cellstr(name);


legendName1 = "in to tree";
legendName2 = "old town cross";
legendName3 = "park joy";
legendName4 = "ducks take off";


% Compression ratio by block size (no quantization)
figure(1)
hold on

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{1});
scatter(blockSize(mask), compressionRatio(mask), 10, "green", 'filled', 'DisplayName', legendName1)

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{361});
scatter(blockSize(mask), compressionRatio(mask), 10, "black", 'filled', 'DisplayName', legendName2)

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{721});
scatter(blockSize(mask), compressionRatio(mask), 10, "blue", 'filled', 'DisplayName', legendName3)

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{1081});
scatter(blockSize(mask), compressionRatio(mask), 10, "red", 'filled', 'DisplayName', legendName4)
hold off


legend(legendName1, legendName2, legendName3, legendName4);
xlabel('Block Size');
ylabel('Compression Ratio');
title('Compression ratio by block size (no quantization)');

% Compression ratio by block size (4 quantization in all channels)
figure(2)
hold on

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1});
scatter(blockSize(mask), compressionRatio(mask), 10, "green", 'filled', 'DisplayName', legendName1)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{361});
scatter(blockSize(mask), compressionRatio(mask), 10, "black", 'filled', 'DisplayName', legendName2)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{721});
scatter(blockSize(mask), compressionRatio(mask), 10, "blue", 'filled', 'DisplayName', legendName3)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1081});
scatter(blockSize(mask), compressionRatio(mask), 10, "red", 'filled', 'DisplayName', legendName4)
hold off


legend(legendName1, legendName2, legendName3, legendName4);
xlabel('Block Size');
ylabel('Compression Ratio');
title('Compression ratio by block size (4 quantization bits/channel)');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Compression ratio by search area (no quantization)
figure(3)
hold on

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{1});
scatter(searchArea(mask), compressionRatio(mask), 10, "green", 'filled', 'DisplayName', legendName1)

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{361});
scatter(searchArea(mask), compressionRatio(mask), 10, "black", 'filled', 'DisplayName', legendName2)

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{721});
scatter(searchArea(mask), compressionRatio(mask), 10, "blue", 'filled', 'DisplayName', legendName3)

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{1081});
scatter(searchArea(mask), compressionRatio(mask), 10, "red", 'filled', 'DisplayName', legendName4)
hold off


legend(legendName1, legendName2, legendName3, legendName4);
xlabel('Search area');
ylabel('Compression Ratio');
title('Compression ratio by search area (no quantization)');

% Compression ratio by block size (4 quantization in all channels)
figure(4)
hold on

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1});
scatter(searchArea(mask), compressionRatio(mask), 10, "green", 'filled', 'DisplayName', legendName1)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{361});
scatter(searchArea(mask), compressionRatio(mask), 10, "black", 'filled', 'DisplayName', legendName2)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{721});
scatter(searchArea(mask), compressionRatio(mask), 10, "blue", 'filled', 'DisplayName', legendName3)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1081});
scatter(searchArea(mask), compressionRatio(mask), 10, "red", 'filled', 'DisplayName', legendName4)
hold off


legend(legendName1, legendName2, legendName3, legendName4);
xlabel('Search area');
ylabel('Compression Ratio');
title('Compression ratio by search area (4 quantization bits/channel)');


% PSNR by block size (4 quantization bits/channel)
figure(5)
hold on

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1});
scatter(searchArea(mask), PSNR(mask), 10, "green", 'filled', 'DisplayName', legendName1)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{361});
scatter(searchArea(mask), PSNR(mask), 10, "black", 'filled', 'DisplayName', legendName2)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{721});
scatter(searchArea(mask), PSNR(mask), 10, "blue", 'filled', 'DisplayName', legendName3)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1081});
scatter(searchArea(mask), PSNR(mask), 10, "red", 'filled', 'DisplayName', legendName4)
hold off


legend(legendName1, legendName2, legendName3, legendName4);
xlabel('Search area');
ylabel('PSNR');
title('PSNR by search area (4 quantization bits/channel)');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Compression ratio by search area (no quantization)
figure(6)
hold on

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{1});
scatter(keyframePeriod(mask), compressionRatio(mask), 10, "green", 'filled', 'DisplayName', legendName1)

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{361});
scatter(keyframePeriod(mask), compressionRatio(mask), 10, "black", 'filled', 'DisplayName', legendName2)

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{721});
scatter(keyframePeriod(mask), compressionRatio(mask), 10, "blue", 'filled', 'DisplayName', legendName3)

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & strcmp(name, name{1081});
scatter(keyframePeriod(mask), compressionRatio(mask), 10, "red", 'filled', 'DisplayName', legendName4)
hold off


legend(legendName1, legendName2, legendName3, legendName4);
xlabel('Search area');
ylabel('Compression Ratio');
title('Compression ratio by keyframe period (no quantization)');

% Compression ratio by block size (4 quantization in all channels)
figure(7)
hold on

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1});
scatter(keyframePeriod(mask), compressionRatio(mask), 10, "green", 'filled', 'DisplayName', legendName1)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{361});
scatter(keyframePeriod(mask), compressionRatio(mask), 10, "black", 'filled', 'DisplayName', legendName2)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{721});
scatter(keyframePeriod(mask), compressionRatio(mask), 10, "blue", 'filled', 'DisplayName', legendName3)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1081});
scatter(keyframePeriod(mask), compressionRatio(mask), 10, "red", 'filled', 'DisplayName', legendName4)
hold off


legend(legendName1, legendName2, legendName3, legendName4);
xlabel('Search area');
ylabel('Compression Ratio');
title('Compression ratio by keyframe period (4 quantization bits/channel)');


% PSNR by block size (4 quantization bits/channel)
figure(8)
hold on

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1});
scatter(keyframePeriod(mask), PSNR(mask), 10, "green", 'filled', 'DisplayName', legendName1)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{361});
scatter(keyframePeriod(mask), PSNR(mask), 10, "black", 'filled', 'DisplayName', legendName2)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{721});
scatter(keyframePeriod(mask), PSNR(mask), 10, "blue", 'filled', 'DisplayName', legendName3)

mask = quantizationY == 4 & quantizationU == 4 & quantizationV == 4 & strcmp(name, name{1081});
scatter(keyframePeriod(mask), PSNR(mask), 10, "red", 'filled', 'DisplayName', legendName4)
hold off


legend(legendName1, legendName2, legendName3, legendName4);
xlabel('Keyframe period');
ylabel('PSNR');
title('PSNR by Keyframe period (4 quantization bits/channel)');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(9)
hold on

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{1});
scatter(PSNR(mask), compressionRatio(mask), 10, "green", 'filled', 'DisplayName', legendName1);

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{361});
scatter(PSNR(mask), compressionRatio(mask), 10, "black", 'filled', 'DisplayName', legendName2);

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{721});
scatter(PSNR(mask), compressionRatio(mask), 10, "blue", 'filled', 'DisplayName', legendName3);

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{1081});
scatter(PSNR(mask), compressionRatio(mask), 10, "red", 'filled', 'DisplayName', legendName4);

hold off

legend('Location', 'Best');
xlabel('PSNR');
ylabel('Compression Ratio');
title('PSNR by compression ratio');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(10)
hold on

quant_averages = (quantizationY + quantizationU + quantizationV)/3;

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{1});
scatter(quant_averages(mask), PSNR(mask), 10, "green", 'filled', 'DisplayName', legendName1);

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{361});
scatter(quant_averages(mask), PSNR(mask), 10, "black", 'filled', 'DisplayName', legendName2);

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{721});
scatter(quant_averages(mask), PSNR(mask), 10, "blue", 'filled', 'DisplayName', legendName3);

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{1081});
scatter(quant_averages(mask), PSNR(mask), 10, "red", 'filled', 'DisplayName', legendName4);

hold off

legend('Location', 'Best');
xlabel('Quantization Avg.');
ylabel('PSNR');
title('PSNR by quantization avg. (of all channels)');



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(11)
hold on


mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{1});
scatter(compressionRatio(mask), executionTime(mask), 10, "green", 'filled', 'DisplayName', legendName1);

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{361});
scatter(compressionRatio(mask), executionTime(mask), 10, "black", 'filled', 'DisplayName', legendName2);

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{721});
scatter(compressionRatio(mask), executionTime(mask), 10, "blue", 'filled', 'DisplayName', legendName3);

mask = blockSize == 16 & searchArea == 16 & keyframePeriod == 10 & strcmp(name, name{1081});
scatter(compressionRatio(mask), executionTime(mask), 10, "red", 'filled', 'DisplayName', legendName4);

hold off

legend('Location', 'Best');
xlabel('Compression ratio.');
ylabel('Execution time');
title('Execution time by compression ratio');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


figure(12)
hold on

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & blockSize == 16 & keyframePeriod == 10 & strcmp(name, name{1});
scatter(searchArea(mask), executionTime(mask), 50, "green", 'filled', 'DisplayName', legendName1);

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & blockSize == 16 & keyframePeriod == 10 & strcmp(name, name{361});
scatter(searchArea(mask), executionTime(mask), 50, "black", 'filled', 'DisplayName', legendName2);

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & blockSize == 16 & keyframePeriod == 10 & strcmp(name, name{721});
scatter(searchArea(mask), executionTime(mask), 50, "blue", 'filled', 'DisplayName', legendName3);

mask = quantizationY == 0 & quantizationU == 0 & quantizationV == 0 & blockSize == 16 & keyframePeriod == 10 & strcmp(name, name{1081});
scatter(searchArea(mask), executionTime(mask), 50, "red", 'filled', 'DisplayName', legendName4);

hold off

legend('Location', 'Best');
xlabel('Search Area.');
ylabel('Execution time');
title('Execution time by search area');







