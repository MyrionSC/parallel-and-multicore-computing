seqExeTimes = [32.43 0.0 0.0 0.0 0.0 0.0];                             
parExeTimes = [23.34 12.65 6.56 3.57 0.0 0.0];
allExeTimes = horzcat(seqExeTimes(:), parExeTimes(:));
ticks = [1 2 3 4 5 6];
tickLabels = {1 2 4 8 16 32};

bar(allExeTimes);

title('Execution times vs. number of cores');
ax = gca;

xlabel('Number of cores')
set(gca, 'XTick', ticks);
set(gca, 'XTickLabel', tickLabels);

ylabel('Execution time in seconds');
ax.YGrid = 'on';

hold on

plot(parExeTimes)
