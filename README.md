# Skywatch-Asteroid-Observation-Station
Problem Statement
When an asteroid comes close to Earth, multiple organizations may want to observe it using telescopes. However, an observation station has a limited number of telescopes.
Without a proper system, it becomes difficult to:
Manage multiple observation requests.
Decide who gets a telescope first.
Track available and busy telescopes.
Avoid assigning one telescope to multiple organizations.
Project Summary
Our project provides a simple way to manage asteroid observation requests and limited telescope resources. It organizes requests in FIFO order using a Queue and tracks telescope availability using an Array. This helps reduce confusion, manage resources efficiently, and ensure fair access to telescopes.
Used Data Structures
1.Queue:
The Queue stores all incoming asteroid observation requests from different organizations. Each request is added to the rear of the queue and processed from the front, following the FIFO (First In, First Out) principle. When a telescope becomes available, the first waiting request is assigned to it and removed from the queue.
2.Array:
The Array stores the available telescopes and their current status. Each telescope has a position in the array, along with its name and whether it is free or busy. When assigning a telescope, the system searches the array for a free telescope and changes its status to busy. After the observation is finished, its status is changed back to free.

Limitations
We could have added a password system to secure the Observation Station Admin panel, but we did not include it because our main focus is on the Queue and Array implementation required for the Data Structure course.
