#pragma once
class BlockSettings {
    public:
        BlockSettings() {}

        /**
         * Checks if the block is solid ground, meaning players and objects will
         * not fall through.
         * 
         * @return true if the block is solid, false otherwise.
         */
        bool isSolid() {
            return isSolid_;
        }

        /**
         * Checks if the block has collision, disallowing players to pass through it.
         * 
         * @return true if the block has collision, false otherwise.
         */
        bool hasCollision() {
            return hasCollision_;
        }
        
        /**
         * Checks if the block is affected by gravity, meaning it will fall down
         * until it reaches stable ground.
         * 
         * @return true if the block is affected by gravity, false otherwise.
         */
        bool hasGravity() {
            return hasGravity_;
        }
        
        /**
         * Checks if the block can be pushed by players.
         * 
         * @return true if the block can be pushed, false otherwise.
         */
        bool isPushable() {
            return isPushable_;
        }

        /**
         * Checks if the block is lethal to players, causing them to be killed instantly upon contact.
         * 
         * @return true if the block is lethal, false otherwise.
         */
        bool isLethal() {
            return isLethal_;
        }

        /**
         * Checks if the block is brittle, meaning it will fall or break 
         * when a player passes over it.
         * 
         * @return true if the block is brittle, false otherwise.
         */
        bool isBrittle() {
            return isBrittle_;
        }

        /**
         * Checks if the block is climbable from the top, allowing players above to climb down.
         * 
         * @return true if the block is climbable from the top, false otherwise.
         */
        bool isClimbableFromTop() {
            return isClimbableFromTop_;
        }
        
        /**
         * Checks if the block is climbable from the bottom, allowing players to climb up.
         * 
         * @return true if the block is climbable from the bottom, false otherwise.
         */
        bool isClimbableFromBottom() {
            return isClimbableFromBottom_;
        }

        friend class BlockSettingsBuilder;

    private:
        bool isSolid_ = true;
        bool isPushable_ = false;
        bool isClimbableFromTop_ = false;
        bool isClimbableFromBottom_ = false;
        bool isLethal_ = false;
        bool isBrittle_ = false;
        bool hasCollision_ = false;
        bool hasGravity_ = false;
};
class BlockSettingsBuilder {
    public:
        /**
         * Marks the block non-solid, letting players and objects fall through.
         * 
         * @return BlockSettingsBuilder with changed settings
         */
        BlockSettingsBuilder nonSolid() {
            blockSettings.isSolid_ = false;
            return *this;
        }
        /**
         * Makes the block pushable by players.
         *
         * @return BlockSettingsBuilder with changed settings
         */
        BlockSettingsBuilder pushable() {
            blockSettings.isPushable_ = true;
            return *this;
        }
        /**
         * Marks the block as collidable, disallowing players to pass through it.
         *
         * @return BlockSettingsBuilder with changed settings
         */
        BlockSettingsBuilder collidable() {
            blockSettings.hasCollision_ = true;
            return *this;
        }
        /**
         * Marks the block as affected by gravity, making it fall down until it reaches stable ground.
         *
         * @return BlockSettingsBuilder with changed settings
         */
        BlockSettingsBuilder gravity() {
            blockSettings.hasGravity_ = true;
            return *this;
        }
        /**
         * Makes the block lethal to players, killing them instantly if they touch it.
         *
         * @return BlockSettingsBuilder with changed settings
         */
        BlockSettingsBuilder lethal() {
            blockSettings.isLethal_ = true;
            return *this;
        }
        /**
         * Makes the block brittle, making it fall down when a player passes over it.
         *
         * @return BlockSettingsBuilder with changed settings
         */
        BlockSettingsBuilder brittle() {
            blockSettings.isBrittle_ = true;
            return *this;
        }
        /**
         * Marks the block as climbable from the top, allowing players above to climb down.
         *
         * @return BlockSettingsBuilder with changed settings
         */
        BlockSettingsBuilder climbableFromTop() {
            blockSettings.isClimbableFromTop_ = true;
            return *this;
        }
        /**
         * Marks the block as climbable from the bottom, allowing players below to climb up.
         * 
         * @return BlockSettingsBuilder with changed settings
         */
        BlockSettingsBuilder climbableFromBottom() {
            blockSettings.isClimbableFromBottom_ = true;
            return *this;
        }
        /**
         * Returns the built BlockSettings object.
         *
         * @return BlockSettings object with the set properties
         */
        BlockSettings build() {
            return blockSettings;
        }
    private:
        BlockSettings blockSettings = BlockSettings();
};