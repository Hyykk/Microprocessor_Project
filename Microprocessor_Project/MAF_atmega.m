data = [];
filtered_in_atmega128 = [];

windowSize = 10;  % 이동평균 필터 윈도우 크기

filteredData = movmean(data, windowSize);  % 이동평균 필터링

% 그래프 그리기
figure;
subplot(2,1,1);
    hold on;
    plot(data, '-k', 'LineWidth', 1.5);  % 원본 데이터 (파란색 선)
    plot(filtered_in_atmega128, '-r', 'LineWidth', 1.5);  % 필터링된 데이터 (빨간색 선)
    plot(filteredData, '-b', 'LineWidth', 1.5);  % 필터링된 데이터 (빨간색 선)
    legend('Original Data', 'Filtered in atmega128','Filtered in Matlab');
    %legend('Original Data', 'Filtered in Matlab');
    xlabel('Time Domain');
    ylabel('Resistance Domain');
    title('MAF Filtering (Windowsize : 10)');
    grid on;

subplot(2,1,2);
    hold on;
    Fs = 1;  % 샘플링 주파수
    N = length(data);  % 데이터 포인트의 개수
    f = (0:N-1)*(Fs/N);  % 주파수 벡터
    
    data_fft = fft(data);  % FFT 적용
    fa_fft = fft(filtered_in_atmega128);  % FFT 적용
    fm_fft = fft(filteredData);  % FFT 적용
    
    stem(f, abs(data_fft), 'k', 'LineWidth', 2.0);  % 주파수 영역의 그래프 (파란색 선)
    stem(f, abs(fa_fft), 'r', 'LineWidth', 1.5);  % 주파수 영역의 그래프 (파란색 선)
    stem(f, abs(fm_fft), 'b', 'LineWidth', 1.0);  % 주파수 영역의 그래프 (파란색 선)

    xlabel('Frequency (Hz)');
    ylabel('Magnitude');
    legend('Original Data', 'Filtered in Atmega128','Filtered in Matlab');
    %legend('Original Data', 'Filtered in Matlab');
    title('FFT');
    grid on;