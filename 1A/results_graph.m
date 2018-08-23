clear all
close all

seqExeTimes = [36.214 0.0 0.0 0.0 0.0];                             
parExeTimes = [23.666 14.822 7.164 3.960 1.488];
allExeTimes = horzcat(seqExeTimes(:), parExeTimes(:));
ticks = [1 2 3 4 5];
tickLabels = {1 2 4 8 12};

bar(allExeTimes);

title('Execution times vs. number of cores (2000n-5000e)');
ax = gca;

xlabel('Number of cores')
set(gca, 'XTick', ticks);
set(gca, 'XTickLabel', tickLabels);

ylabel('Execution time in seconds');
ax.YGrid = 'on';

hold on

plot(parExeTimes)

legend('Sequential execution time', 'Parallel execution time', 'Parallel linear prediction')
