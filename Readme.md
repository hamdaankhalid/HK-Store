## File-Polling Based NGINX Traffic Dashboard For Observability
  
  I recently deployed an app behind NGINX, when needing to debug or check traffic I had to rely heavily on viewing the log files which were verbose and offered hard to infer data.

  The data is of time series nature and a log summarizer, and traffic dashboard will come in hand for me to increase my server's observability.

#### Program Objective
  Code will be compiled to a single binary that will take log and error log files as input, upon kicking it off it will start a dashboard in the terminal that will give me insight from the log files, with a refresh of every 5 seconds to give me view of updated results.
  
  Dashboard will include metrics such as website hits, traffic per unit, number of total error logs.

#### Software Architecture
  - Driver code
  - PolledFile: Handles file polling, and log aggregation.
  - 
  