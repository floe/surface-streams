gst-launch-1.0 -ve udpsrc port=5000 ! application/x-rtp, media=video, clock-rate=90000, encoding-name=MP2T ! rtpjitterbuffer ! rtpmp2tdepay ! tsparse ! tsdemux name=mux \
	mux. ! h264parse ! queue leaky=downstream ! avdec_h264 ! videoconvert ! fpsdisplaysink sync=false \
	mux. ! h264parse ! queue leaky=downstream ! avdec_h264 ! videoconvert ! fpsdisplaysink sync=false \
	mux. ! queue leaky=downstream ! opusdec ! autoaudiosink sync=false